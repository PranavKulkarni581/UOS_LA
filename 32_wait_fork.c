#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    if(pid==0){
        printf("Child: sleeping 2s\n");
        sleep(2);
        _exit(5);
    } else {
        int status;
        printf("Parent: waiting for child\n");
        wait(&status);
        if(WIFEXITED(status)) printf("Child exited with %d\n", WEXITSTATUS(status));
    }
    return 0;
}
