#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
    FILE *f; char buf[4096];
    if(argc==1){
        while(fgets(buf,sizeof(buf),stdin)) fputs(buf,stdout);
    } else {
        for(int i=1;i<argc;i++){
            f=fopen(argv[i],"r");
            if(!f){ perror("fopen"); continue; }
            while(fgets(buf,sizeof(buf),f)) fputs(buf,stdout);
            fclose(f);
        }
    }
    return 0;
}
