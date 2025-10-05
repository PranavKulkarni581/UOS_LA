#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(){
    int fd=open("flockfile.txt", O_RDWR|O_CREAT, 0666);
    if(fd<0) return 1;
    struct flock fl={F_WRLCK, SEEK_SET, 0, 0, 0};
    printf("Attempting flock lock...\n");
    if(fcntl(fd,F_SETLKW,&fl)==0){ printf("Locked. Writing...\n"); write(fd,"Locked\n",7); fl.l_type=F_UNLCK; fcntl(fd,F_SETLK,&fl); printf("Unlocked\n"); }
    close(fd); return 0;
}
