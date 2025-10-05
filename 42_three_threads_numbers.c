#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *evens(void *arg){
    for(int i=0;i<=10;i+=2){ printf("Even: %d\n", i); sleep(1); } return NULL;
}
void *odds(void *arg){
    for(int i=1;i<=9;i+=2){ printf("Odd: %d\n", i); sleep(1); } return NULL;
}
int isprime(int n){ if(n<2) return 0; for(int i=2;i*i<=n;i++) if(n%i==0) return 0; return 1; }
void *primes(void *arg){
    for(int i=2;i<=30;i++){ if(isprime(i)) printf("Prime: %d\n", i); sleep(1); } return NULL;
}

int main(){
    pthread_t t1,t2,t3;
    pthread_create(&t1,NULL,evens,NULL);
    pthread_create(&t2,NULL,odds,NULL);
    pthread_create(&t3,NULL,primes,NULL);
    pthread_join(t1,NULL); pthread_join(t2,NULL); pthread_join(t3,NULL);
    return 0;
}
