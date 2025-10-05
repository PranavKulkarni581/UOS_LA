#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    printf("Demo exec variants. This program will exec /bin/ls using execl, execv, execvp.\n");
    if(fork()==0){
        execl("/bin/ls","ls","-l",(char*)NULL);
        perror("execl");
        _exit(1);
    }
    wait(NULL);
    if(fork()==0){
        char *args[]={"/bin/ls","-a",NULL};
        execv("/bin/ls",args);
        perror("execv");
        _exit(1);
    }
    wait(NULL);
    if(fork()==0){
        char *args2[]={"ls","-h",NULL};
        execvp("ls",args2);
        perror("execvp");
        _exit(1);
    }
    wait(NULL);
    return 0;
}
