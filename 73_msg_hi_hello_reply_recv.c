#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg{ long mtype; char mtext[128]; };

int main(){
    key_t k = ftok(".", 'D');
    int q = msgget(k, IPC_CREAT | 0666);
    struct msg r;
    msgrcv(q,&r,128,2,0);
    printf("Received reply: %s\n", r.mtext);
    // then send "I am fine"
    struct msg s; s.mtype=1; strcpy(s.mtext,"I am fine");
    msgsnd(q,&s,strlen(s.mtext)+1,0);
    return 0;
}
