#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int s){
    printf("Received signal %d\n", s);
}

int main(){
    printf("Receiver PID: %d\n", getpid());
    signal(SIGUSR1, handler);
    while(1) pause();
    return 0;
}
