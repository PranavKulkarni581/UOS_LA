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
    m.mtype = 1;
    strcpy(m.mtext, "Hi?");
    msgsnd(q,&m,strlen(m.mtext)+1,0);
    printf("Sent: %s\n", m.mtext);
    return 0;
}
