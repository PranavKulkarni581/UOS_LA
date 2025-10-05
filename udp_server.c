#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

unsigned long long factorial(int n) {
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) fact *= i;
    return fact;
}

int main() {
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    printf("UDP Server listening on port %d...\n", PORT);

    int n;
    recvfrom(sockfd, &n, sizeof(n), 0, (struct sockaddr*)&client, &len);
    printf("Received number: %d\n", n);

    unsigned long long fact = factorial(n);
    sendto(sockfd, &fact, sizeof(fact), 0, (struct sockaddr*)&client, len);

    close(sockfd);
    return 0;
}
