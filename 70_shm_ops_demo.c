#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

#define KEY 0x5300
int main(){
    int shmid = shmget(KEY, 128, 0666 | IPC_CREAT);
    printf("Created shm id %d\n", shmid);
    char *p = shmat(shmid,NULL,0);
    printf("Attached at %p\n", p);
    sprintf(p, "Hello from process %d\n", getpid());
    printf("Data written. Detaching...\n");
    shmdt(p);
    printf("Detached. Removing segment.\n");
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
