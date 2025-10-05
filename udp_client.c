#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server;
    socklen_t len = sizeof(server);
    int num;
    unsigned long long fact;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    printf("Enter a number: ");
    scanf("%d", &num);

    sendto(sockfd, &num, sizeof(num), 0, (struct sockaddr*)&server, len);
    recvfrom(sockfd, &fact, sizeof(fact), 0, (struct sockaddr*)&server, &len);

    printf("Factorial: %llu\n", fact);

    close(sockfd);
    return 0;
}
