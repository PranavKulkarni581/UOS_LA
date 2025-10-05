#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in server, client;
    socklen_t addrlen = sizeof(client);
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(sockfd, 5);

    printf("Iterative Echo Server listening on port %d...\n", PORT);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr*)&client, &addrlen);
        int n = read(newsockfd, buffer, BUF_SIZE);
        buffer[n] = '\0';
        printf("Received: %s\n", buffer);
        write(newsockfd, buffer, n);
        close(newsockfd);
    }

    close(sockfd);
    return 0;
}
