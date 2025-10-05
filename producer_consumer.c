#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 5
#define ITEMS 10

union semun { int val; struct semid_ds *buf; unsigned short *array; };

struct shared {
    int buffer[BUFFER_SIZE];
    int in, out;
};

int main() {
    key_t key = ftok(".", 'P');
    int shmid = shmget(key, sizeof(struct shared), 0666 | IPC_CREAT);
    struct shared *sh = (struct shared*) shmat(shmid, NULL, 0);
    sh->in = sh->out = 0;

    int semid = semget(key, 3, 0666 | IPC_CREAT);
    union semun u;
    u.val = BUFFER_SIZE; semctl(semid, 0, SETVAL, u); // empty
    u.val = 0; semctl(semid, 1, SETVAL, u);           // full
    u.val = 1; semctl(semid, 2, SETVAL, u);           // mutex

    pid_t pid = fork();

    if (pid == 0) { // Producer
        for (int i = 1; i <= ITEMS; i++) {
            struct sembuf ops[2];
            ops[0].sem_num = 0; ops[0].sem_op = -1; ops[0].sem_flg = 0; // wait empty
            ops[1].sem_num = 2; ops[1].sem_op = -1; ops[1].sem_flg = 0; // wait mutex
            semop(semid, ops, 2);

            sh->buffer[sh->in] = i;
            printf("Produced: %d\n", i);
            sh->in = (sh->in + 1) % BUFFER_SIZE;

            struct sembuf ops2[2];
            ops2[0].sem_num = 2; ops2[0].sem_op = 1; ops2[0].sem_flg = 0;  // signal mutex
            ops2[1].sem_num = 1; ops2[1].sem_op = 1; ops2[1].sem_flg = 0;  // signal full
            semop(semid, ops2, 2);
            sleep(1);
        }
        _exit(0);
    } else { // Consumer
        for (int i = 1; i <= ITEMS; i++) {
            struct sembuf ops[2];
            ops[0].sem_num = 1; ops[0].sem_op = -1; ops[0].sem_flg = 0; // wait full
            ops[1].sem_num = 2; ops[1].sem_op = -1; ops[1].sem_flg = 0; // wait mutex
            semop(semid, ops, 2);

            int item = sh->buffer[sh->out];
            printf("Consumed: %d\n", item);
            sh->out = (sh->out + 1) % BUFFER_SIZE;

            struct sembuf ops2[2];
            ops2[0].sem_num = 2; ops2[0].sem_op = 1; ops2[0].sem_flg = 0;  // signal mutex
            ops2[1].sem_num = 0; ops2[1].sem_op = 1; ops2[1].sem_flg = 0;  // signal empty
            semop(semid, ops2, 2);
            sleep(2);
        }
        wait(NULL);
        shmdt(sh);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}
