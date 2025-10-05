#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
int main(){
    int p[2]; pipe(p);
    if(fork()==0){
        close(p[1]); char c; while(read(p[0],&c,1)>0){ putchar(tolower(c)); } _exit(0);
    } else {
        close(p[0]); char buf[1024]; while(fgets(buf,sizeof(buf),stdin)) write(p[1],buf,strlen(buf)); close(p[1]); wait(NULL);
    }
    return 0;
}
