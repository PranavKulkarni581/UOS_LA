#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUF_SIZE 5
int buffer[BUF_SIZE]; int in=0,out=0;
sem_t empty, full, mutex;

void *producer(void *arg){
    int id = (int)(long)arg;
    for(int i=0;i<10;i++){
        sem_wait(&empty); sem_wait(&mutex);
        buffer[in]=i; printf("Producer %d produced %d\n", id, i);
        in=(in+1)%BUF_SIZE;
        sem_post(&mutex); sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg){
    int id=(int)(long)arg;
    for(int i=0;i<10;i++){
        sem_wait(&full); sem_wait(&mutex);
        int v=buffer[out]; printf("Consumer %d consumed %d\n", id, v);
        out=(out+1)%BUF_SIZE;
        sem_post(&mutex); sem_post(&empty);
        sleep(2);
    }
    return NULL;
}

int main(){
    pthread_t p1,p2,c1,c2;
    sem_init(&empty,0,BUF_SIZE); sem_init(&full,0,0); sem_init(&mutex,0,1);
    pthread_create(&p1,NULL,producer,(void*)1); pthread_create(&p2,NULL,producer,(void*)2);
    pthread_create(&c1,NULL,consumer,(void*)1); pthread_create(&c2,NULL,consumer,(void*)2);
    pthread_join(p1,NULL); pthread_join(p2,NULL); pthread_join(c1,NULL); pthread_join(c2,NULL);
    return 0;
}
