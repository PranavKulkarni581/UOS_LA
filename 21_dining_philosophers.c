#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
sem_t forks[N];
sem_t room;

void *philosopher(void *arg){
    int id = (int)(long)arg;
    while(1){
        printf("Philosopher %d is thinking\n", id);
        sleep(1);
        sem_wait(&room);
        sem_wait(&forks[id]);
        sem_wait(&forks[(id+1)%N]);
        sem_post(&room);
        printf("Philosopher %d is eating\n", id);
        sleep(2);
        sem_post(&forks[id]);
        sem_post(&forks[(id+1)%N]);
        printf("Philosopher %d finished eating\n", id);
        sleep(1);
    }
    return NULL;
}

int main(){
    pthread_t tid[N];
    sem_init(&room,0,N-1); // allow at most N-1 philosophers to try pick forks
    for(int i=0;i<N;i++) sem_init(&forks[i],0,1);
    for(long i=0;i<N;i++) pthread_create(&tid[i],NULL,philosopher,(void*)i);
    for(int i=0;i<N;i++) pthread_join(tid[i],NULL);
    return 0;
}
