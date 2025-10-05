#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define KEY 0x5100
#define SIZE 8192

int main(int argc,char *argv[]){
    if(argc<3){ printf("Usage: %s write <infile> | read <outfile>\n", argv[0]); return 1; }
    int shmid = shmget(KEY, SIZE, 0666 | IPC_CREAT);
    char *p = (char*)shmat(shmid,NULL,0);
    if(strcmp(argv[1],"write")==0){
        FILE *f=fopen(argv[2],"rb"); if(!f){ perror("fopen"); return 1; }
        int n=fread(p,1,SIZE,f); p[n]=0; fclose(f); printf("Written %d bytes to shm\n", n);
    } else {
        FILE *f=fopen(argv[2],"wb"); if(!f){ perror("fopen"); return 1; }
        fwrite(p,1,strlen(p),f); fclose(f); printf("Read from shm to file\n");
    }
    return 0;
}
