#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

volatile sig_atomic_t timed_out = 0;
jmp_buf env;

void alrm(int s){
    timed_out = 1;
    longjmp(env,1);
}

int main(){
    signal(SIGALRM, alrm);
    alarm(5);
    if(setjmp(env)==0){
        char buf[128];
        printf("You have 5 seconds to enter input: ");
        fflush(stdout);
        if(fgets(buf,sizeof(buf),stdin)){
            alarm(0);
            printf("Input: %s", buf);
        }
    } else {
        printf("\nTime expired!\n");
    }
    return 0;
}
