#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    char username[128]={0}, password[128]={0};
    pid_t pid = vfork();
    if(pid==0){
        printf("Child: Enter username: ");
        fflush(stdout);
        if(fgets(username,sizeof(username),stdin)){};
        _exit(0);
    } else {
        wait(NULL);
        printf("Parent: Enter password: ");
        fflush(stdout);
        if(fgets(password,sizeof(password),stdin)){};
        printf("Collected username: %sPassword: %s", username, password);
    }
    return 0;
}
