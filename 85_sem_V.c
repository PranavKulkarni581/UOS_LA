#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main(){ key_t k=ftok(".", 'S'); int id=semget(k,1,0); struct sembuf op={0,1,0}; semop(id,&op,1); printf("V performed\n"); return 0; }
