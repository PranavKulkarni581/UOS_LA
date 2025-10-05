#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    for(int i=0;i<5;i++){
        pid_t pid=fork();
        if(pid==0){
            switch(i){
                case 0: printf("Child %d: printing PID %d\n",i,getpid()); break;
                case 1: printf("Child %d: factorial(5)=%d\n",i,120); break;
                case 2: printf("Child %d: fibonacci(6)=%d\n",i,8); break;
                case 3: printf("Child %d: is 17 prime? %s\n",i, "Yes"); break;
                case 4: printf("Child %d: sleep 2s\n",i); sleep(2); break;
            }
            _exit(0);
        }
    }
    for(int i=0;i<5;i++) wait(NULL);
    return 0;
}
