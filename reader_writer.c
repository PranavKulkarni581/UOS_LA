#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

union semun { int val; struct semid_ds *buf; unsigned short *array; };

int main() {
    key_t key = ftok(".", 'R');
    int semid = semget(key, 2, 0666 | IPC_CREAT);
    union semun u;
    u.val = 1; semctl(semid, 0, SETVAL, u); // mutex
    u.val = 1; semctl(semid, 1, SETVAL, u); // write

    int shmid = shmget(key + 1, sizeof(int), 0666 | IPC_CREAT);
    int *readcount = (int*) shmat(shmid, NULL, 0);
    *readcount = 0;

    for (int i = 0; i < 2; i++) { // 2 readers
        if (fork() == 0) {
            for (int j = 0; j < 3; j++) {
                struct sembuf wait_mutex = {0, -1, 0};
                struct sembuf signal_mutex = {0, 1, 0};
                struct sembuf wait_write = {1, -1, 0};
                struct sembuf signal_write = {1, 1, 0};

                semop(semid, &wait_mutex, 1);
                (*readcount)++;
                if (*readcount == 1) semop(semid, &wait_write, 1);
                semop(semid, &signal_mutex, 1);

                printf("Reader %d is reading...\n", i + 1);
                sleep(1);

                semop(semid, &wait_mutex, 1);
                (*readcount)--;
                if (*readcount == 0) semop(semid, &signal_write, 1);
                semop(semid, &signal_mutex, 1);

                sleep(1);
            }
            _exit(0);
        }
    }

    if (fork() == 0) { // Writer
        for (int i = 0; i < 3; i++) {
            struct sembuf wait_write = {1, -1, 0};
            struct sembuf signal_write = {1, 1, 0};
            semop(semid, &wait_write, 1);
            printf("Writer is writing...\n");
            sleep(2);
            semop(semid, &signal_write, 1);
            sleep(1);
        }
        _exit(0);
    }

    while (wait(NULL) > 0); // wait for all children
    shmdt(readcount);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
