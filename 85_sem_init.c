#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main(){ key_t k=ftok(".", 'S'); int id=semget(k,1,0666|IPC_CREAT); printf("Semaphore id: %d\n", id); return 0; }
