#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    if(argc<2){ printf("Usage: %s <program> [args...]\n",argv[0]); return 1; }
    pid_t pid = fork();
    if(pid==0){
        execvp(argv[1], &argv[1]);
        perror("execvp");
        _exit(1);
    } else {
        wait(NULL);
    }
    return 0;
}
