#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define PORT 9092
#define BUF 2048

unsigned long long factorial(int n){ unsigned long long f=1; for(int i=1;i<=n;i++) f*=i; return f; }
void reverse_str(char *s){ int n=strlen(s); for(int i=0;i<n/2;i++){ char t=s[i]; s[i]=s[n-i-1]; s[n-i-1]=t; } }

int main(){
    int sock=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv,cli; socklen_t len=sizeof(cli);
    serv.sin_family=AF_INET; serv.sin_addr.s_addr=INADDR_ANY; serv.sin_port=htons(PORT);
    bind(sock,(struct sockaddr*)&serv,sizeof(serv)); listen(sock,10);
    printf("Distributed compute server on port %d\n",PORT);
    while(1){
        int ns=accept(sock,(struct sockaddr*)&cli,&len);
        if(ns<0) continue;
        if(fork()==0){
            close(sock);
            char buf[BUF];
            int n=read(ns,buf,BUF-1);
            if(n<=0){ close(ns); _exit(0); }
            buf[n]=0;
            // protocol: <cmd> <arg>\n e.g., FACT 5  or REV hello
            char cmd[32], arg[BUF];
            sscanf(buf,"%s %[^\n]",cmd,arg);
            if(strcmp(cmd,"FACT")==0){
                int v=atoi(arg);
                unsigned long long res=factorial(v);
                dprintf(ns,"%llu\n",res);
            } else if(strcmp(cmd,"REV")==0){
                reverse_str(arg);
                dprintf(ns,"%s\n",arg);
            } else if(strcmp(cmd,"MAT")==0){
                // not implemented fully; echo back
                dprintf(ns,"MAT not implemented in demo\n");
            } else dprintf(ns,"Unknown command\n");
            close(ns); _exit(0);
        }
        close(ns);
        while(waitpid(-1,NULL,WNOHANG)>0);
    }
    close(sock);
    return 0;
}
