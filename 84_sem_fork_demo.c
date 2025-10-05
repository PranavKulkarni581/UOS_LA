#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    sem_t *s = sem_open("/demo_sem", O_CREAT, 0666, 0);
    if(fork()==0){
        printf("Child waiting...\n"); sem_wait(s); printf("Child proceeding\n"); _exit(0);
    } else {
        sleep(1); printf("Parent posting\n"); sem_post(s); wait(NULL);
        sem_unlink("/demo_sem");
    }
    return 0;
}
