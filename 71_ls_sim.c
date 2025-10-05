#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
int main(int argc,char *argv[]){
    const char *path = (argc>1)?argv[1]:".";
    DIR *d = opendir(path);
    if(!d){ perror("opendir"); return 1; }
    struct dirent *e;
    while((e=readdir(d))){ if(e->d_name[0]=='.') continue; printf("%s  ", e->d_name); }
    printf("\n"); closedir(d); return 0;
}
