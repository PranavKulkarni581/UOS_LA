#include <stdio.h>
#include <pthread.h>

void *worker(void *arg){ printf("Hello from thread %ld\n", (long)arg); return NULL; }

int main(){
    pthread_t t[5];
    for(long i=0;i<5;i++) pthread_create(&t[i],NULL,worker,(void*)i);
    for(int i=0;i<5;i++) pthread_join(t[i],NULL);
    return 0;
}
