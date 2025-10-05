#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_mode(mode_t m){
    printf( (S_ISDIR(m)) ? "d" : "-");
    printf( m & S_IRUSR ? "r" : "-");
    printf( m & S_IWUSR ? "w" : "-");
    printf( m & S_IXUSR ? "x" : "-");
    printf( m & S_IRGRP ? "r" : "-");
    printf( m & S_IWGRP ? "w" : "-");
    printf( m & S_IXGRP ? "x" : "-");
    printf( m & S_IROTH ? "r" : "-");
    printf( m & S_IWOTH ? "w" : "-");
    printf( m & S_IXOTH ? "x\n" : "-\n");
}

int main(int argc,char *argv[]){
    if(argc<2){ printf("Usage: %s <file>\n",argv[0]); return 1; }
    struct stat st;
    if(stat(argv[1], &st)!=0){ perror("stat"); return 1; }
    printf("File: %s\n", argv[1]);
    printf("Size: %lld\n", (long long)st.st_size);
    printf("Permissions: "); print_mode(st.st_mode);
    printf("UID: %d (%s)\n", st.st_uid, getpwuid(st.st_uid)->pw_name);
    printf("GID: %d (%s)\n", st.st_gid, getgrgid(st.st_gid)->gr_name);
    printf("Last modified: %s", ctime(&st.st_mtime));
    return 0;
}
