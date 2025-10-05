#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

void reverseString(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n/2; i++) {
        char temp = str[i];
        str[i] = str[n-i-1];
        str[n-i-1] = temp;
    }
}

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

    printf("Server listening on port %d...\n", PORT);
    newsockfd = accept(sockfd, (struct sockaddr*)&client, &addrlen);

    int n = read(newsockfd, buffer, BUF_SIZE);
    buffer[n] = '\0';

    printf("Received from client: %s\n", buffer);
    reverseString(buffer);

    write(newsockfd, buffer, strlen(buffer));
    close(newsockfd);
    close(sockfd);
    return 0;
}
