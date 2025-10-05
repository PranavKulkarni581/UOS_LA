#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    for(int i=0;i<3;i++){
        pid_t pid=fork();
        if(pid==0){
            printf("Child %d pid=%d exiting with %d\n",i,getpid(),i+1);
            _exit(i+1);
        }
    }
    for(int i=0;i<3;i++){
        int status;
        pid_t c = wait(&status);
        if(WIFEXITED(status)){
            printf("Parent collected child %d exit=%d\n", c, WEXITSTATUS(status));
        }
    }
    return 0;
}
