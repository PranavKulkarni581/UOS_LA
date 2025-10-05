#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, write_sem;
int readcount=0;

void *reader(void *arg){
    int id=(int)(long)arg;
    for(int i=0;i<3;i++){
        sem_wait(&mutex);
        readcount++; if(readcount==1) sem_wait(&write_sem);
        sem_post(&mutex);
        printf("Reader %d reading\n", id); sleep(1);
        sem_wait(&mutex);
        readcount--; if(readcount==0) sem_post(&write_sem);
        sem_post(&mutex);
        sleep(1);
    }
    return NULL;
}

void *writer(void *arg){
    int id=(int)(long)arg;
    for(int i=0;i<3;i++){
        sem_wait(&write_sem);
        printf("Writer %d writing\n", id); sleep(2);
        sem_post(&write_sem); sleep(1);
    }
    return NULL;
}

int main(){
    pthread_t r1,r2,w1;
    sem_init(&mutex,0,1); sem_init(&write_sem,0,1);
    pthread_create(&r1,NULL,reader,(void*)1);
    pthread_create(&r2,NULL,reader,(void*)2);
    pthread_create(&w1,NULL,writer,(void*)1);
    pthread_join(r1,NULL); pthread_join(r2,NULL); pthread_join(w1,NULL);
    return 0;
}
