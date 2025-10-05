#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    key_t key = ftok(".", 'S');
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    pid_t pid = fork();

    if (pid > 0) {
        char *str = (char*)shmat(shmid, NULL, 0);
        printf("Enter a string: ");
        fgets(str, 1024, stdin);
        shmdt(str);
        wait(NULL);
        shmctl(shmid, IPC_RMID, NULL);
    } else {
        sleep(2);
        char *str = (char*)shmat(shmid, NULL, 0);
        printf("Received: %s", str);
        shmdt(str);
        _exit(0);
    }
    return 0;
}
