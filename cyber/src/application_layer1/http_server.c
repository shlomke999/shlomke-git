#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>

#define PORT 8000
#define BUFFER_SIZE 1024
#define SERVER_ROOT "."

void handle_http_request(int new_sock) 
{
    char buffer[BUFFER_SIZE];
    char method[256];
    char url[256];
    char* response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    read(new_sock, buffer, sizeof(buffer) - 1);

    printf("client HTTP Request =\n%s\n", buffer);


    sscanf(buffer, "%[^ ] %[^ ]", method, url);

    printf("\nMethod = %s, URL = %s\n", method, url);


    write(new_sock, response, strlen(response));
    close(new_sock);
}

int main() 
{
    int server_fd, new_sock;
    struct sockaddr_in server_addr, client_addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&server_addr , sizeof(server_addr));/*bind socket to port*/
    listen(server_fd, 10);

    printf("HTTP Server running on port %d\n", PORT);

    while(1) 
    {
        socklen_t sin_len = sizeof(client_addr);
        new_sock = accept(server_fd, (struct sockaddr *) &client_addr, &sin_len);

        if (!fork()) 
        {
            close(server_fd);
            handle_http_request(new_sock);
            exit(0);
        } 
        else
        {
            close(new_sock);
        }
    }
    return 0;
}
