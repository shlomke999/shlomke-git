#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <sys/select.h>/*select*/
#include <stdio.h>     /*printf*/
#include <stdlib.h>    /**/
#include <string.h>    /*bzero*/
#include <unistd.h>
#include <sys/socket.h>/*socket*/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>/*ioctl*/
#include <fcntl.h>    /*fcntl*/
#include <signal.h>   /*signals catching*/
#include <netdb.h>
#include <linux/if.h> /*tun*/
#include <linux/if_tun.h>/*tun*/
#include <netinet/in.h>/*inet_addr*/
#include <arpa/inet.h> /*inet_addr*/

#define AS_CLIENT YES      /*make sure to comment this line on the server side*/
#define SERVER_IP "10.0.2.4"
#define CLIENT_IP "10.0.2.15"

#define MAX2(X, Y) (((X) > (Y)) ? (X) : (Y))
#define PORT 54345
#define MTU 1400
#define BIND_HOST "0.0.0.0"

/* Create VPN interface /dev/tun0 and return its fd */
int tun_alloc()
{
  struct ifreq interface;
  int fd, e;

  if ((fd = open("/dev/net/tun", O_RDWR)) < 0)
  {
    perror("open /dev/net/tun failed");
    exit(1);
  }

  memset(&interface, 0, sizeof(interface));

  interface.ifr_flags = IFF_TUN | IFF_NO_PI;
  strncpy(interface.ifr_name, "tun0", IFNAMSIZ);

  /*define the interface to be type tune and ready for communication*/
  if ((e = ioctl(fd, TUNSETIFF, (void *)&interface)) < 0)
  {
    perror("ioctl failed!");
    close(fd);
    exit(1);
  }

  return fd;
}

/* Execute commands */
static void Run(char *cmd)
{
  printf("Execute `%s`\n", cmd);
  if (system(cmd))
  {
    perror(cmd);
    exit(1);
  }
}

/* Setup routing via iptables & ip route*/
void setup_route_table()
{
  char cmd[255];
  char cmd2[255];
  Run("sysctl -w net.ipv4.ip_forward=1");
#ifdef AS_CLIENT
  snprintf(cmd, sizeof(cmd), "ifconfig tun0 10.8.0.2/16 mtu %d up", MTU);
#else
  snprintf(cmd, sizeof(cmd), "ifconfig tun0 10.8.0.1/16 mtu %d up", MTU);
#endif
  Run(cmd);

#ifdef AS_CLIENT
  snprintf(cmd2, sizeof(cmd2), "ip route add %s via %s", SERVER_IP, CLIENT_IP);
  Run(cmd2);
  Run("ip route add 0/1 dev tun0");
  Run("ip route add 128/1 dev tun0");
#else
  Run("iptables -t nat -A POSTROUTING -s 10.8.0.0/16 ! -d 10.8.0.0/16 -j MASQUERADE");
#endif
}

void cleanup_route_table()
{
#ifdef AS_CLIENT
  char cmd[1024];
  snprintf(cmd, sizeof(cmd), "ip route del %s", SERVER_IP);
  Run(cmd);
  Run("ip route del 0/1");
  Run("ip route del 128/1");
#else
  Run("iptables -t nat -D POSTROUTING -s 10.8.0.0/16 ! -d 10.8.0.0/16 -j MASQUERADE");
#endif
}

/* create UDP socket */
int udp_bind(struct sockaddr *addr, socklen_t *addrlen)
{
  struct addrinfo hints;
  struct addrinfo *result;
  int sock, flags;

#ifdef AS_CLIENT
  const char *host = SERVER_IP;
#else
  const char *host = BIND_HOST;
#endif

  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_protocol = IPPROTO_UDP;

  if (0 != getaddrinfo(host, NULL, &hints, &result)) /*return addrinfo struct, which contains an Internet address that we will specified in the call to bind*/
  {
    perror("getaddrinfo error");
    return -1;
  }
  ((struct sockaddr_in *)result->ai_addr)->sin_port = htons(PORT); /*change the port to network byte order(big indian)*/

  memcpy(addr, result->ai_addr, result->ai_addrlen);
  *addrlen = result->ai_addrlen;

  if (-1 == (sock = socket(result->ai_family, SOCK_DGRAM, IPPROTO_UDP)))
  {
    perror("Cannot create socket");
    freeaddrinfo(result);
    return -1;
  }

#ifndef AS_CLIENT
  if (0 != bind(sock, result->ai_addr, result->ai_addrlen)) /*bind the socket with the address returned from getaddrinfo(0.0.0.0)*/

  {
    perror("bind socket failed");
    close(sock);
    freeaddrinfo(result);
    return -1;
  }
#endif
  freeaddrinfo(result);

  flags = fcntl(sock, F_GETFL, 0);
  if (flags != -1)
  {
    if (-1 != fcntl(sock, F_SETFL, flags | O_NONBLOCK))
      return sock;
  }
  perror("fcntl error");
  close(sock);
  return -1;
}

/* Catch Ctrl-C and `kill`s, make sure route table gets cleaned before this process exit */
void cleanup(int signo)
{
  printf("exiting....\n");
  if (signo == SIGHUP || signo == SIGINT || signo == SIGTERM)
  {
    cleanup_route_table();
    exit(0);
  }
}

void cleanup_when_sig_exit()
{
  struct sigaction sa;
  sa.sa_handler = &cleanup;
  sa.sa_flags = SA_RESTART;
  sigfillset(&sa.sa_mask);

  if (sigaction(SIGHUP, &sa, NULL) < 0)
  {
    perror("Cannot handle SIGHUP");
  }
  if (sigaction(SIGINT, &sa, NULL) < 0)
  {
    perror("Cannot handle SIGINT");
  }
  if (sigaction(SIGTERM, &sa, NULL) < 0)
  {
    perror("Cannot handle SIGTERM");
  }
}

int encryption(char *origin, char *output, int len, int mode)
{
  memcpy(output, origin, len);
  return 0;
}

int main(int argc, char **argv)
{
  int tun_fd;
  int udp_fd;
  struct sockaddr_storage client_addr;
  socklen_t client_addrlen = sizeof(client_addr);
  char tun_buf[MTU], udp_buf[MTU];

  if ((tun_fd = tun_alloc()) < 0)
  {
    perror("tun create failed");
    exit(1);
  }

  setup_route_table();
  cleanup_when_sig_exit();

  if ((udp_fd = udp_bind((struct sockaddr *)&client_addr, &client_addrlen)) < 0)
  {
    perror("failed to Bind udp");
    exit(1);
  }

  bzero(tun_buf, MTU);
  bzero(udp_buf, MTU);

  while (1)
  {
    int r;
    int max_fd = MAX2(tun_fd, udp_fd) + 1;
    fd_set readset;
    FD_ZERO(&readset);
    FD_SET(tun_fd, &readset);
    FD_SET(udp_fd, &readset);

    if (-1 == select(max_fd, &readset, NULL, NULL, NULL))
    {
      perror("select error");
      break;
    }

    if (FD_ISSET(tun_fd, &readset))/*if we have traffic from inside processes*/
    {
      r = read(tun_fd, tun_buf, MTU);/*read from tun_fd to tun_buff*/
      if (r < 0)
      {
        perror("read from tun_fd error");
        break;
      }

      encryption(tun_buf, udp_buf, r, 0);/*copy from tun_buf to udp_buf*/

      /*send udp buff with encapsulation and encryption on udp_fd*/
      r = sendto(udp_fd, udp_buf, r, 0, (const struct sockaddr *)&client_addr, client_addrlen);
      if (r < 0)
      {
        perror("sendto udp_fd error");
        break;
      }
    }

    if (FD_ISSET(udp_fd, &readset))/*if we have traffic from outside (the server/client)*/
    {
      r = recvfrom(udp_fd, udp_buf, MTU, 0, (struct sockaddr *)&client_addr, &client_addrlen);/*recieve to buff and pill the encapsulation*/
      if (r < 0)
      {
        perror("recvfrom udp_fd error");
        break;
      }

      encryption(udp_buf, tun_buf, r, 1);/*copy from udp_buff to tun_buf*/

      r = write(tun_fd, tun_buf, r);/*write it from buff to tun_fd (we don't use sendto because we don't need encapsulate)*/
      if (r < 0)
      {
        perror("write tun_fd error");
        break;
      }
    }
  }

  close(tun_fd);
  close(udp_fd);
  cleanup_route_table();
}


/* 1. ip forwarding on the client, server, and also on the host.
   2. client routing table: - all traffic will go to the vnic for encapsulation.
                            - traffic destinate to server will go to the physical nic.
   3. server - iptables MASQUERADE rule. */