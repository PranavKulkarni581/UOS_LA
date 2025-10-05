#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void notify(int s){
    printf("\nAlarm! Time's up.\n");
}

int main(int argc,char *argv[]){
    int secs=5;
    if(argc>1) secs = atoi(argv[1]);
    signal(SIGALRM, notify);
    printf("Alarm set for %d seconds\n", secs);
    alarm(secs);
    pause();
    return 0;
}
