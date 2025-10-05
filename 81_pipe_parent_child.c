#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(){
    int p[2]; pipe(p);
    if(fork()==0){ close(p[1]); char buf[100]; read(p[0],buf,100); printf("Child got: %s\n", buf); _exit(0); }
    else{ close(p[0]); char *msg="Hello from parent"; write(p[1],msg,strlen(msg)+1); wait(NULL); }
    return 0;
}
