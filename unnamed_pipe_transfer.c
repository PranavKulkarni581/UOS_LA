// 1. unnamed_pipe_transfer.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
int main(int argc,char *argv[]){
    if(argc<2) return 1;
    int fd=open(argv[1],O_RDONLY);
    if(fd<0) return 1;
    int p[2];
    if(pipe(p)==-1) return 1;
    pid_t pid=fork();
    if(pid>0){
        close(p[0]);
        char buf[1024];
        ssize_t r;
        while((r=read(fd,buf,sizeof(buf)))>0) write(p[1],buf,r);
        close(p[1]);
        close(fd);
        wait(NULL);
    }else if(pid==0){
        close(p[1]);
        char buf[1024];
        ssize_t r;
        while((r=read(p[0],buf,sizeof(buf)))>0) write(STDOUT_FILENO,buf,r);
        close(p[0]);
        _exit(0);
    }
    return 0;
}
