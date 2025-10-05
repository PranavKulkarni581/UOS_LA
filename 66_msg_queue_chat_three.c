#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define KEY 0x4000
#define MSGLEN 256
struct msg{ long mtype; char mtext[MSGLEN]; };

int main(int argc,char *argv[]){
    if(argc!=2){ printf("Usage: %s <id 1|2|3>\n",argv[0]); return 1; }
    int id = atoi(argv[1]);
    int q = msgget(KEY, IPC_CREAT | 0666);
    struct msg m;
    pid_t pid=fork();
    if(pid==0){
        while(1){
            msgrcv(q,&m,MSGLEN,0,0);
            printf("Got (type %ld): %s\n", m.mtype, m.mtext);
        }
    } else {
        char buf[MSGLEN];
        while(fgets(buf,MSGLEN,stdin)){
            m.mtype = id;
            strncpy(m.mtext, buf, MSGLEN);
            msgsnd(q,&m,strlen(m.mtext)+1,0);
        }
    }
    return 0;
}
