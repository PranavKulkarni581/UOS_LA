#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

union semun { int val; struct semid_ds *buf; unsigned short *array; };

int main() {
    key_t key = ftok(".", 'E');
    int semid = semget(key, 2, 0666 | IPC_CREAT);
    union semun u;
    u.val = 1; semctl(semid, 0, SETVAL, u);  // even semaphore
    u.val = 0; semctl(semid, 1, SETVAL, u);  // odd semaphore

    pid_t pid = fork();
    struct sembuf p = {0, -1, 0}, v = {1, +1, 0};
    if (pid == 0) {
        for (int i = 1; i <= 9; i += 2) {
            struct sembuf waitOdd = {1, -1, 0};
            struct sembuf signalEven = {0, +1, 0};
            semop(semid, &waitOdd, 1);
            printf("%d ", i);
            fflush(stdout);
            semop(semid, &signalEven, 1);
        }
        _exit(0);
    } else {
        for (int i = 0; i <= 8; i += 2) {
            struct sembuf waitEven = {0, -1, 0};
            struct sembuf signalOdd = {1, +1, 0};
            semop(semid, &waitEven, 1);
            printf("%d ", i);
            fflush(stdout);
            semop(semid, &signalOdd, 1);
        }
        wait(NULL);
        printf("\n");
        semctl(semid, 0, IPC_RMID);
    }
    return 0;
}
