#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>

#define KEY 0x5200
int main(){
    int shmid = shmget(KEY, 4096, 0666 | IPC_CREAT);
    int *p = (int*) shmat(shmid,NULL,0);
    pid_t p1 = fork();
    if(p1==0){
        int n; printf("Enter n: "); scanf("%d",&n); p[0]=n;
        for(int i=1;i<=n;i++) scanf("%d",&p[i]);
        _exit(0);
    }
    wait(NULL);
    pid_t p2=fork();
    if(p2==0){
        int n=p[0];
        for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) if(p[i]>p[j]){ int t=p[i]; p[i]=p[j]; p[j]=t; }
        _exit(0);
    }
    wait(NULL);
    pid_t p3=fork();
    if(p3==0){
        int n=p[0]; printf("Sorted: "); for(int i=1;i<=n;i++) printf("%d ",p[i]); printf("\n"); _exit(0);
    }
    wait(NULL);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
