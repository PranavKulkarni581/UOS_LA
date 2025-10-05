#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_KEY 0x1234
#define SEM_KEY 0x2345
#define BUF_SIZE 5
#define TOTAL_ITEMS 20

struct shm_struct { int buffer[BUF_SIZE]; int in, out; };

union semun { int val; };

void sem_op(int semid,int num,int op){ struct sembuf s={num,op,0}; semop(semid,&s,1); }

int main(){
    int shmid=shmget(SHM_KEY,sizeof(struct shm_struct),0666|IPC_CREAT);
    struct shm_struct *sh=(struct shm_struct*)shmat(shmid,NULL,0);
    sh->in=sh->out=0;
    int semid=semget(SEM_KEY,3,0666|IPC_CREAT);
    union semun u;
    u.val=BUF_SIZE; semctl(semid,0,SETVAL,u); // empty
    u.val=0; semctl(semid,1,SETVAL,u); // full
    u.val=1; semctl(semid,2,SETVAL,u); // mutex

    for(int p=0;p<2;p++){
        if(fork()==0){
            for(int i=0;i<TOTAL_ITEMS/2;i++){
                sem_op(semid,0,-1);
                sem_op(semid,2,-1);
                sh->buffer[sh->in]=i + p*(TOTAL_ITEMS/2);
                printf("Producer %d produced %d\n",p,sh->buffer[sh->in]);
                sh->in=(sh->in+1)%BUF_SIZE;
                sem_op(semid,2,1);
                sem_op(semid,1,1);
                sleep(1);
            }
            _exit(0);
        }
    }

    for(int c=0;c<2;c++){
        if(fork()==0){
            for(int i=0;i<TOTAL_ITEMS/2;i++){
                sem_op(semid,1,-1);
                sem_op(semid,2,-1);
                int val=sh->buffer[sh->out];
                printf("Consumer %d consumed %d\n",c,val);
                sh->out=(sh->out+1)%BUF_SIZE;
                sem_op(semid,2,1);
                sem_op(semid,0,1);
                sleep(2);
            }
            _exit(0);
        }
    }

    for(int i=0;i<4;i++) wait(NULL);
    shmdt(sh);
    shmctl(shmid,IPC_RMID,NULL);
    semctl(semid,0,IPC_RMID);
    return 0;
}
