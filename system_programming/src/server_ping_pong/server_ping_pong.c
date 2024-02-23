#include <fcntl.h> /* fcntl */
#include <arpa/inet.h> /* htonl, htons */
#include <errno.h>/*perror*/
#include <netinet/in.h> /* sockaddr_in */
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit*/
#include <string.h> /* strlen */
#include <strings.h> /* bzero */
#include <sys/select.h> /* fd_set, select */
#include <sys/socket.h> /* socklen_t, socket operations */
#include <sys/types.h>
#include <unistd.h>/*sleep, close*/

#include "server_ping_pong.h"
#define PORT 5000
#define MAXLINE 1024
#define MAX_CONNECTIONS 10

static void LogToFile(char *msg)
{
    FILE *log_file = fopen("tcp_client_log.txt", "a");
    if (!log_file)
    {
        perror("can't open log file\n");
        return;
    }
    fwrite(msg, 1, strlen(msg), log_file);
    fclose(log_file);
}

void TcpServerHandler(int tcp_fd, int *arr,struct sockaddr_in client_address, socklen_t len)
{
    int i = 0;
    int connection = accept(tcp_fd, (struct sockaddr*)&client_address, &len);
    if (connection < 0)
    {
        perror("accept failed");
    }
    for(i = 0; i < MAX_CONNECTIONS; ++i)
    {
        if (arr[i] < 0)
        {
            arr[i] = connection;
            break;
        }
    }
}

TcpConnectionHandler(int *arr, struct sockaddr_in client_address, fd_set descriptor_set)
{
    int i = 0, res;
    char buffer[MAXLINE];
    socklen_t len = sizeof(client_address);

    for(i = 3; i < MAX_CONNECTIONS; ++i)
    {
        if (arr[i] > 0 && FD_ISSET(arr[i], &descriptor_set))
        {
            res = recvfrom(arr[i], buffer, sizeof(buffer), 0,
                        (struct sockaddr*)&client_address, &len);
            if (res == 0)/*connection closed(0 bytes recived)*/
            {
                arr[i] = -1;
                bzero(buffer, sizeof(buffer));
                LogToFile("TCP connection ended\n");
            }
            printf("%s\n", "Message From TCP client: ");
            puts(buffer);
            sendto(arr[i], (const char*)"pong", sizeof(buffer), 0,
                (struct sockaddr*)&client_address, sizeof(client_address));
        }
    }
}


void Server()
{
    int all_connections[MAX_CONNECTIONS];
	int tcp_fd, connected_fd, udp_fd, max_fd, a;
	char buffer[MAXLINE], stdin_buffer[MAXLINE];
	fd_set descriptor_set;
	socklen_t len;
    struct timeval timeout;
	struct sockaddr_in client_address, servaddr;
	char* message = "pong";

	/*create TCP and UDP sockets*/
	tcp_fd = socket(AF_INET, SOCK_STREAM, 0);/*AF_INET = ipv4(AF - address family)*/
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	udp_fd = socket(AF_INET, SOCK_DGRAM, 0);

	/*binding server addr to the sockes*/
	bind(tcp_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(tcp_fd, 10);
	bind(udp_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    for(a = 0; a < MAX_CONNECTIONS; ++a)
    {
        (all_connections[a] = -1);
    }
    all_connections[0] = tcp_fd;
    all_connections[1] = udp_fd;
    all_connections[2] = fileno(stdin);
    
	while (1) 
    {
        timeout.tv_sec = 7;
        timeout.tv_usec = 0;

        FD_ZERO(&descriptor_set);

		/*add sockets to set*/
        for(a = 0; a < MAX_CONNECTIONS; ++a)
        {
            if (all_connections[a] >= 0)
            {
		        FD_SET(all_connections[a], &descriptor_set);
            }
            fcntl(all_connections[a], F_SETFL, O_NONBLOCK);/*non blocking state*/
        }

		/*select ready descriptor from set*/
		if (0 == select(FD_SETSIZE, &descriptor_set, NULL, NULL, &timeout))
        {
            LogToFile("inactive for 7 seconds\n");
        }

		if (FD_ISSET(tcp_fd, &descriptor_set)) 
        {
            TcpServerHandler(tcp_fd, all_connections, client_address, len);
		}
		else if (FD_ISSET(udp_fd, &descriptor_set)) 
        {
			len = sizeof(client_address);
			bzero(buffer, sizeof(buffer));
            /*read msg (ping) from client to buffer through udp_fd*/
			recvfrom(udp_fd, buffer, sizeof(buffer), 0,
						(struct sockaddr*)&client_address, &len);
			printf("%s\n", "Message From UDP client: ");
			puts(buffer);
			sendto(udp_fd, (const char*)message, sizeof(buffer), 0,
				(struct sockaddr*)&client_address, sizeof(client_address));
		}
        else if (FD_ISSET(fileno(stdin), &descriptor_set))
        {
            fgets(stdin_buffer, MAXLINE, stdin) ;
            *(stdin_buffer + strlen(stdin_buffer) - 1) = '\0';    
            
            if (0 == strcmp(stdin_buffer,"quit"))
            {
                printf("quiting... \n");
                break; 
            }           
            if (0 == strcmp(stdin_buffer,"ping"))
            {
                printf("pong\n");
            }     	
         }

        TcpConnectionHandler(all_connections, client_address, descriptor_set);
	}
}


void TCPClient()
{
    int socket_fd, res = 0;
    char buffer[MAXLINE];
    const char *message = "Ping";
    struct sockaddr_in servaddr;
    size_t sleep_count = 2, i = 5;
    socklen_t len;
 
    /* Creating socket file descriptor */
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation failed in TCPClient");
        exit(0);
    }
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (res = connect(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        LogToFile("TCP connection failed.\n");
        printf("Error : Connect Failed \n");
    }
    else
    {
        LogToFile("TCP connection established.\n");
    }
    for (; i > 0; --i)
    {
        sendto(socket_fd, message, strlen(message), 0, 
                (const struct sockaddr*)&servaddr, sizeof(servaddr));
        LogToFile("sent TCP packet\n");
        printf("Message from server: ");
        recvfrom(socket_fd, (char*)buffer, MAXLINE, 0,                
                    (struct sockaddr*)&servaddr, &len);
        LogToFile("TCP client recived response\n");
        puts(buffer);
        printf("Sleep for %lu sec\n", sleep_count);
        sleep(sleep_count);
    }
    close(socket_fd);
}


void UDPClient()
{
    int socket_fd;
    char buffer[MAXLINE];
    char* message = "Ping";
    struct sockaddr_in servaddr;
    socklen_t len;
    size_t sleep_count = 2, i = 5;
 
    /* Creating socket file descriptor */
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        perror("Socket creation failed");
        exit(0);
    }
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    for (; i > 0; --i)
    {
        /*Send ping message to server*/
        sendto(socket_fd, (const char*)message, strlen(message), 0, 
                (const struct sockaddr*)&servaddr, sizeof(servaddr));
        LogToFile("sent UDP packet\n");
    
        /*receive server's response*/
        printf("Message from server: ");
        recvfrom(socket_fd, (char*)buffer, MAXLINE, 0, 
                    (struct sockaddr*)&servaddr, &len);
        LogToFile("UDP client recived response\n");
        puts(buffer);
        printf("Sleep for %lu sec\n", sleep_count);
        sleep(sleep_count);
    }
    close(socket_fd);
}