#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sockfd, (struct sockaddr*)&server, sizeof(server));

    printf("Enter a message: ");
    fgets(buffer, BUF_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    write(sockfd, buffer, strlen(buffer));

    int n = read(sockfd, buffer, BUF_SIZE);
    buffer[n] = '\0';
    printf("Reversed from server: %s\n", buffer);

    close(sockfd);
    return 0;
}
