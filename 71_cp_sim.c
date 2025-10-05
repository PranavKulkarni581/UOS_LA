#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
    if(argc!=3){ printf("Usage: %s src dst\n",argv[0]); return 1; }
    FILE *in=fopen(argv[1],"rb"), *out=fopen(argv[2],"wb");
    if(!in||!out){ perror("file"); return 1; }
    char buf[4096]; size_t n;
    while((n=fread(buf,1,sizeof(buf),in))>0) fwrite(buf,1,n,out);
    fclose(in); fclose(out); return 0;
}
