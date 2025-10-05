#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc,char *argv[]){
    if(argc<2){ printf("Usage: %s inputfile\n",argv[0]); return 1; }
    int p[2]; pipe(p);
    if(fork()==0){
        close(p[1]); char buf[4096]; int n; while((n=read(p[0],buf,sizeof(buf)))>0) write(1,buf,n); _exit(0);
    } else {
        close(p[0]); int fd=open(argv[1],O_RDONLY); char buf[4096]; int n; while((n=read(fd,buf,sizeof(buf)))>0) write(p[1],buf,n); close(fd); close(p[1]); wait(NULL);
    }
    return 0;
}
