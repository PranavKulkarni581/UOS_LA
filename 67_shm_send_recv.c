#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define KEY 0x5000

int main(int argc,char *argv[]){
    int shmid = shmget(KEY, 4096, 0666 | IPC_CREAT);
    char *p = (char*)shmat(shmid,NULL,0);
    if(argc==1){
        printf("Enter A for A-Z or N for numbers 1-100: ");
        char c=getchar();
        if(c=='A'){ for(int i=0;i<26;i++){ p[i]='A'+i; } p[26]=0; }
        else { char *ptr=p; for(int i=1;i<=100;i++){ ptr+=sprintf(ptr,"%d ", i); } }
        printf("Written to shared memory.\n");
    } else {
        printf("Reader: %s\n", p);
    }
    return 0;
}
