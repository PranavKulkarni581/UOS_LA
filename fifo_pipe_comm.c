// 2. fifo_pipe_comm.c
#include <stdio.h>

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(){
    const char *fifo="/tmp/myfifo_ipc";
    mkfifo(fifo,0666);
    pid_t pid=fork();
    if(pid>0){
        int fd=open(fifo,O_WRONLY);
        char buf[1024];
        while(fgets(buf,sizeof(buf),stdin)){
            write(fd,buf,strlen(buf));
            if(strncmp(buf,"exit",4)==0) break;
        }
        close(fd);
        wait(NULL);
        unlink(fifo);
    }else if(pid==0){
        int fd=open(fifo,O_RDONLY);
        char buf[1024];
        ssize_t r;
        while((r=read(fd,buf,sizeof(buf)-1))>0){
            buf[r]=0;
            write(STDOUT_FILENO,buf,r);
            if(strncmp(buf,"exit",4)==0) break;
        }
        close(fd);
        _exit(0);
    }
    return 0;
}
