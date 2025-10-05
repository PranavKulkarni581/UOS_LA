#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9093
#define MAX_CLIENTS 100
#define BUF 1024

int clients[100];
int count_clients=0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void broadcast(const char *msg, int except_fd){
    pthread_mutex_lock(&lock);
    for(int i=0;i<count_clients;i++){
        if(clients[i]!=except_fd) write(clients[i],msg,strlen(msg));
    }
    pthread_mutex_unlock(&lock);
}

void *handle(void *arg){
    int sock = *(int*)arg;
    char buf[BUF];
    while(1){
        int n = read(sock,buf,BUF-1);
        if(n<=0) break;
        buf[n]=0;
        broadcast(buf,sock);
    }
    close(sock);
    pthread_mutex_lock(&lock);
    for(int i=0;i<count_clients;i++) if(clients[i]==sock){ clients[i]=clients[count_clients-1]; count_clients--; break;}
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(){
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv,cli; socklen_t len=sizeof(cli);
    serv.sin_family=AF_INET; serv.sin_addr.s_addr=INADDR_ANY; serv.sin_port=htons(PORT);
    bind(listenfd,(struct sockaddr*)&serv,sizeof(serv)); listen(listenfd,10);
    printf("Chat server on port %d\n",PORT);
    while(1){
        int ns=accept(listenfd,(struct sockaddr*)&cli,&len);
        pthread_mutex_lock(&lock);
        clients[count_clients++]=ns;
        pthread_mutex_unlock(&lock);
        pthread_t tid; pthread_create(&tid,NULL,handle,&ns); pthread_detach(tid);
    }
    close(listenfd);
    return 0;
}
