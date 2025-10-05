#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg{ long mtype; char mtext[128]; };

int main(){
    key_t k = ftok(".", 'D');
    int q = msgget(k, IPC_CREAT | 0666);
    struct msg m;
    msgrcv(q,&m,128,1,0);
    printf("Received: %s\n", m.mtext);
    // reply
    struct msg r; r.mtype=2; strcpy(r.mtext,"Hello");
    msgsnd(q,&r,strlen(r.mtext)+1,0);
    return 0;
}
