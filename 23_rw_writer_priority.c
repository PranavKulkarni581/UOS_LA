#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

#define SEM_KEY 0x3000
#define SHM_KEY 0x3001

union semun { int val; };

void sem_op(int semid,int num,int op){ struct sembuf s={num,op,0}; semop(semid,&s,1); }

int main(){
    int semid=semget(SEM_KEY,3,0666|IPC_CREAT);
    union semun u; u.val=1; semctl(semid,0,SETVAL,u); // mutex
    u.val=1; semctl(semid,1,SETVAL,u); // resource
    u.val=0; semctl(semid,2,SETVAL,u); // write_q (writers waiting count as semaphore value holder)

    int shmid=shmget(SHM_KEY,sizeof(int),0666|IPC_CREAT);
    int *readcount=(int*)shmat(shmid,NULL,0);
    *readcount=0;

    if(fork()==0){ // writer
        for(int i=0;i<3;i++){
            sem_op(semid,2,1); // increment writers waiting (using sempahore as counter)
            sem_op(semid,1,-1); // wait resource
            sem_op(semid,2,-1); // decrement writers waiting
            printf("Writer writing...\n");
            sleep(2);
            sem_op(semid,1,1);
            sleep(1);
        }
        _exit(0);
    }

    if(fork()==0){ // multiple readers
        for(int r=0;r<5;r++){
            sem_op(semid,0,-1);
            while(semctl(semid,2,GETVAL,0) > 0) { /* busy wait while writers waiting to give priority */ usleep(1000); }
            (*readcount)++;
            if(*readcount==1) sem_op(semid,1,-1);
            sem_op(semid,0,1);

            printf("Reader reading...\n");
            sleep(1);

            sem_op(semid,0,-1);
            (*readcount)--;
            if(*readcount==0) sem_op(semid,1,1);
            sem_op(semid,0,1);
            sleep(1);
        }
        _exit(0);
    }

    wait(NULL);
    wait(NULL);
    shmdt(readcount);
    shmctl(shmid,IPC_RMID,NULL);
    semctl(semid,0,IPC_RMID);
    return 0;
}
