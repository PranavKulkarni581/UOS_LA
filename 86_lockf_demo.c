#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(){
    int fd=open("lockfile.txt", O_RDWR|O_CREAT, 0666);
    if(fd<0) return 1;
    printf("Acquiring lockf lock...\n");
    if(lockf(fd,F_LOCK,0)==0){ printf("Locked. Writing...\n"); write(fd,"Locked\n",7); sleep(5); lockf(fd,F_ULOCK,0); printf("Unlocked\n"); }
    close(fd); return 0;
}
