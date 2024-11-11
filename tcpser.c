/* tcpser.c */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

#define PORT 8181
#define BUFFER_SIZE 512

int server_socket;

void handle_sigint(int sig) {
    printf("\nShutting down server...\n");
    if (server_socket > 0) {
        close(server_socket);
    }
    exit(0);
}

int main()
{
    int client_socket;
    struct sockaddr_in srv, cli;
    socklen_t addrlen;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];
    char *data;

    memset(&srv, 0, sizeof(srv));
    memset(&cli, 0, sizeof(cli));

    signal(SIGINT, handle_sigint);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("Socket creation failed. Could not create socket");
        return -1;
    }

    srv.sin_port = htons(PORT);
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&srv, sizeof(srv)) != 0)
    {
        perror("Bind failed. Could not bind to the specified port");
        close(server_socket);
        return -1;
    }

    if (listen(server_socket, 5))
    {
        perror("Listen failed. Unable to listen for incoming connections");
        close(server_socket);
        return -1;
    }
    printf("Listening on 0.0.0.0:%d\n", PORT);

    addrlen = sizeof(cli);
    client_socket = accept(server_socket, (struct sockaddr *)&cli, &addrlen);
    if (client_socket < 0)
    {
        perror("Accept failed. Unable to accept incoming connection");
        close(server_socket);
        return -1;
    }

    printf("Client connected\n");

    bytes_read = read(client_socket, buffer, BUFFER_SIZE);
    if (bytes_read < 0)
    {
        perror("Error reading data from the client socket");
    }
    else {
        printf("Received data: %s\n", buffer);
    }

    data = "httpd v1.0\n";
    ssize_t bytes_sent = write(client_socket, data, strlen(data));
    if (bytes_sent < 0)
    {
        perror("Error sending response to the client socket");
    }

    close(client_socket);
    close(server_socket);

    return 0;
}
