#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    key_t key = ftok(".", 'A');
    int shmid = shmget(key, 27, 0666 | IPC_CREAT);
    pid_t pid = fork();

    if (pid > 0) {
        char *data = (char*)shmat(shmid, NULL, 0);
        for (int i = 0; i < 26; i++) data[i] = 'A' + i;
        data[26] = '\0';
        shmdt(data);
        wait(NULL);
        shmctl(shmid, IPC_RMID, NULL);
    } else {
        sleep(1);
        char *data = (char*)shmat(shmid, NULL, 0);
        int fd = open("letters.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        write(fd, data, strlen(data));
        close(fd);
        printf("Data written to letters.txt\n");
        shmdt(data);
        _exit(0);
    }
    return 0;
}
