#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT 8080
#define BUF_SIZE 1024

void sigchld_handler(int s) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
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

    signal(SIGCHLD, sigchld_handler);

    printf("Concurrent Echo Server listening on port %d...\n", PORT);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr*)&client, &addrlen);
        if (newsockfd < 0) continue;

        if (fork() == 0) { // child
            close(sockfd);
            int n;
            while ((n = read(newsockfd, buffer, BUF_SIZE)) > 0) {
                buffer[n] = '\0';
                printf("Received: %s\n", buffer);
                write(newsockfd, buffer, n);
            }
            close(newsockfd);
            _exit(0);
        }
        close(newsockfd); // parent closes client socket
    }

    close(sockfd);
    return 0;
}
