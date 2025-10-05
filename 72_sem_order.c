#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t s;

void *t1(void *arg){ // f1
    sem_wait(&s); // ensure starts after main posts if needed
    printf("f1: username prompt\n");
    sleep(1);
    sem_post(&s); // allow f2
    return NULL;
}

void *t2(void *arg){ // f2
    sem_wait(&s);
    printf("f2: password prompt\n");
    sem_post(&s);
    return NULL;
}

int main(){
    sem_init(&s,0,0);
    pthread_t a,b;
    pthread_create(&a,NULL,t1,NULL);
    pthread_create(&b,NULL,t2,NULL);
    // start f1 by posting once
    sem_post(&s);
    pthread_join(a,NULL); pthread_join(b,NULL);
    sem_destroy(&s);
    return 0;
}
