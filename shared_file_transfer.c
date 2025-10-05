#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define SHM_KEY 1234
#define SEM_KEY 5678
#define CHUNK_SIZE 1024

struct shm_data {
    char buffer[CHUNK_SIZE];
    int size; // number of bytes written
    int eof;  // 1 if end of file
};

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void sem_wait(int semid, int semnum) {
    struct sembuf op = {semnum, -1, 0};
    semop(semid, &op, 1);
}

void sem_signal(int semid, int semnum) {
    struct sembuf op = {semnum, 1, 0};
    semop(semid, &op, 1);
}

int main() {
    char input_file[100], output_file[100];
    printf("Enter input filename: ");
    scanf("%s", input_file);
    printf("Enter output filename: ");
    scanf("%s", output_file);

    int shmid = shmget(SHM_KEY, sizeof(struct shm_data), 0666 | IPC_CREAT);
    struct shm_data *shm = (struct shm_data*) shmat(shmid, NULL, 0);

    int semid = semget(SEM_KEY, 2, 0666 | IPC_CREAT);
    union semun sem_union;
    sem_union.val = 1; semctl(semid, 0, SETVAL, sem_union); // writer can start
    sem_union.val = 0; semctl(semid, 1, SETVAL, sem_union); // reader waits

    pid_t writer = fork();
    if (writer == 0) { // Writer process
        FILE *fp = fopen(input_file, "rb");
        if (!fp) { perror("fopen"); exit(1); }

        while (1) {
            sem_wait(semid, 0);
            shm->size = fread(shm->buffer, 1, CHUNK_SIZE, fp);
            shm->eof = (shm->size < CHUNK_SIZE) ? 1 : 0;
            sem_signal(semid, 1);

            if (shm->eof) break;
        }

        fclose(fp);
        _exit(0);
    }

    pid_t reader = fork();
    if (reader == 0) { // Reader process
        FILE *fp = fopen(output_file, "wb");
        if (!fp) { perror("fopen"); exit(1); }

        while (1) {
            sem_wait(semid, 1);
            fwrite(shm->buffer, 1, shm->size, fp);
            sem_signal(semid, 0);

            if (shm->eof) break;
        }

        fclose(fp);
        _exit(0);
    }

    wait(NULL);
    wait(NULL);

    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
