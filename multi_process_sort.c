#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_KEY 1234
#define SEM_KEY 5678
#define MAX 100

struct data {
    int arr[MAX];
    int n;
    double mean;
    double median;
};

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Semaphore operations
void sem_wait(int semid, int semnum) {
    struct sembuf op = {semnum, -1, 0};
    semop(semid, &op, 1);
}

void sem_signal(int semid, int semnum) {
    struct sembuf op = {semnum, 1, 0};
    semop(semid, &op, 1);
}

int main() {
    int shmid = shmget(SHM_KEY, sizeof(struct data), 0666 | IPC_CREAT);
    struct data *shared = (struct data*) shmat(shmid, NULL, 0);

    int semid = semget(SEM_KEY, 4, 0666 | IPC_CREAT);
    union semun sem_union;
    for (int i = 0; i < 4; i++) {
        sem_union.val = (i==0) ? 1 : 0; // P1 can start immediately
        semctl(semid, i, SETVAL, sem_union);
    }

    pid_t p1 = fork();
    if (p1 == 0) { // Process 1: write array
        sem_wait(semid, 0);
        printf("Enter number of elements: ");
        scanf("%d", &shared->n);
        printf("Enter elements: ");
        for (int i = 0; i < shared->n; i++) scanf("%d", &shared->arr[i]);
        sem_signal(semid, 1); // allow process 2
        _exit(0);
    }

    pid_t p2 = fork();
    if (p2 == 0) { // Process 2: sort
        sem_wait(semid, 1);
        int n = shared->n;
        for (int i = 0; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                if (shared->arr[i] > shared->arr[j]) {
                    int t = shared->arr[i];
                    shared->arr[i] = shared->arr[j];
                    shared->arr[j] = t;
                }
            }
        }
        sem_signal(semid, 2); // allow process 3
        _exit(0);
    }

    pid_t p3 = fork();
    if (p3 == 0) { // Process 3: compute mean & median
        sem_wait(semid, 2);
        int n = shared->n;
        double sum = 0;
        for (int i = 0; i < n; i++) sum += shared->arr[i];
        shared->mean = sum / n;
        if (n % 2 == 0)
            shared->median = (shared->arr[n/2 -1] + shared->arr[n/2]) / 2.0;
        else
            shared->median = shared->arr[n/2];
        sem_signal(semid, 3); // allow process 4
        _exit(0);
    }

    pid_t p4 = fork();
    if (p4 == 0) { // Process 4: display
        sem_wait(semid, 3);
        int n = shared->n;
        printf("Sorted array: ");
        for (int i = 0; i < n; i++) printf("%d ", shared->arr[i]);
        printf("\nMean: %.2lf\nMedian: %.2lf\n", shared->mean, shared->median);
        _exit(0);
    }

    for (int i = 0; i < 4; i++) wait(NULL);

    shmdt(shared);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
