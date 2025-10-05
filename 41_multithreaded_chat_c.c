#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_CLIENTS 10
#define BUF 256

char *clients[MAX_CLIENTS];
int count=0;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

void broadcast(const char *msg){
    pthread_mutex_lock(&lock);
    for(int i=0;i<count;i++) printf("To client %d: %s", i, msg);
    pthread_mutex_unlock(&lock);
}

void *client_thread(void *arg){
    char buf[BUF];
    int id = (int)(long)arg;
    snprintf(buf,sizeof(buf),"Client %d joined\n", id);
    broadcast(buf);
    for(int k=0;k<3;k++){
        snprintf(buf,sizeof(buf),"Message %d from client %d\n", k, id);
        broadcast(buf);
        sleep(1);
    }
    return NULL;
}

int main(){
    pthread_t tids[3];
    for(long i=0;i<3;i++){
        pthread_create(&tids[i],NULL,client_thread,(void*)i);
    }
    for(int i=0;i<3;i++) pthread_join(tids[i],NULL);
    return 0;
}
