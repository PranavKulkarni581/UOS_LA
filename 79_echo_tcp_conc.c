#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#define PORT 9097
void sigchld(int s){ while(waitpid(-1,NULL,WNOHANG)>0); }
int main(){
    int s=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv={AF_INET,htonl(INADDR_ANY),htons(PORT)};
    bind(s,(struct sockaddr*)&serv,sizeof(serv));
    listen(s,10); signal(SIGCHLD,sigchld);
    while(1){
        int c=accept(s,NULL,NULL);
        if(fork()==0){ close(s); char buf[512]; int n; while((n=read(c,buf,511))>0) write(c,buf,n); close(c); _exit(0); }
        close(c);
    }
    close(s); return 0;
}
