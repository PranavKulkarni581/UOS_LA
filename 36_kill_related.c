#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void handler(int s){ printf("Child received SIGTERM\n"); _exit(0); }

int main(){
    pid_t pid=fork();
    if(pid==0){
        signal(SIGTERM, handler);
        printf("Child waiting for signal\n");
        while(1) pause();
    } else {
        sleep(1);
        printf("Parent sending SIGTERM to child %d\n", pid);
        kill(pid, SIGTERM);
        wait(NULL);
    }
    return 0;
}
