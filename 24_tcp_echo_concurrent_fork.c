#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT 9090
#define BUF 1024

void sigchld(int s){ while(waitpid(-1,NULL,WNOHANG)>0); }

int main(){
    int sockfd, newsock;
    struct sockaddr_in serv, cli;
    socklen_t len = sizeof(cli);
    char buf[BUF];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family=AF_INET; serv.sin_addr.s_addr=INADDR_ANY; serv.sin_port=htons(PORT);
    bind(sockfd,(struct sockaddr*)&serv,sizeof(serv));
    listen(sockfd,10);
    signal(SIGCHLD,sigchld);
    printf("Concurrent TCP echo server on port %d\n",PORT);
    while(1){
        newsock = accept(sockfd,(struct sockaddr*)&cli,&len);
        if(newsock<0) continue;
        if(fork()==0){
            close(sockfd);
            ssize_t n;
            while((n=read(newsock,buf,BUF))>0){
                write(newsock,buf,n);
            }
            close(newsock); _exit(0);
        }
        close(newsock);
    }
    close(sockfd);
    return 0;
}
