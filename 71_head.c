#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
    int lines=10; FILE *f=stdin; if(argc>1) f=fopen(argv[1],"r");
    if(!f){ perror("fopen"); return 1; }
    char buf[4096]; int c=0;
    while(fgets(buf,sizeof(buf),f) && c<lines){ fputs(buf,stdout); c++; }
    if(f!=stdin) fclose(f); return 0;
}
