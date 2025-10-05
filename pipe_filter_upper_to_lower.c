// 3. pipe_filter_upper_to_lower.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
int main(){
    int p[2];
    if(pipe(p)==-1) return 1;
    pid_t pid=fork();
    if(pid>0){
        close(p[0]);
        char buf[1024];
        ssize_t r;
        while((r=read(STDIN_FILENO,buf,sizeof(buf)))>0) write(p[1],buf,r);
        close(p[1]);
        wait(NULL);
    }else if(pid==0){
        close(p[1]);
        char c;
        while(read(p[0],&c,1)>0){
            if(c>='A' && c<='Z') c = tolower(c);
            write(STDOUT_FILENO,&c,1);
        }
        close(p[0]);
        _exit(0);
    }
    return 0;
}
