#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    if(argc<2){ printf("Usage: %s <program> [args...]\n",argv[0]); return 1; }
    pid_t pid = vfork();
    if(pid==0){
        execvp(argv[1], &argv[1]);
        _exit(127);
    } else {
        wait(NULL);
    }
    return 0;
}
