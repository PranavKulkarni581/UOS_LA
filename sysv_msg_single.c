// 4. sysv_msg_single.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#define MSGSZ 128
struct msgbuf{ long mtype; char mtext[MSGSZ]; };
int main(){
    key_t key=ftok(".", 'B');
    int msqid=msgget(key, IPC_CREAT | 0666);
    pid_t pid=fork();
    if(pid>0){
        struct msgbuf sb;
        sb.mtype=1;
        strcpy(sb.mtext,"Hello from parent");
        msgsnd(msqid,&sb,strlen(sb.mtext)+1,0);
        wait(NULL);
        msgctl(msqid, IPC_RMID, NULL);
    }else if(pid==0){
        struct msgbuf rb;
        msgrcv(msqid,&rb,MSGSZ,1,0);
        write(STDOUT_FILENO,rb.mtext,strlen(rb.mtext));
        _exit(0);
    }
    return 0;
}
