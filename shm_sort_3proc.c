#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    key_t key = ftok(".", 'T');
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    int n;

    pid_t p1 = fork();
    if (p1 == 0) {
        int *arr = (int*)shmat(shmid, NULL, 0);
        printf("Enter number of elements: ");
        scanf("%d", &n);
        arr[0] = n;
        for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
        shmdt(arr);
        _exit(0);
    }

    wait(NULL);
    pid_t p2 = fork();
    if (p2 == 0) {
        int *arr = (int*)shmat(shmid, NULL, 0);
        int n = arr[0];
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (arr[i] > arr[j]) {
                    int t = arr[i];
                    arr[i] = arr[j];
                    arr[j] = t;
                }
            }
        }
        shmdt(arr);
        _exit(0);
    }

    wait(NULL);
    pid_t p3 = fork();
    if (p3 == 0) {
        int *arr = (int*)shmat(shmid, NULL, 0);
        int n = arr[0];
        printf("Sorted numbers: ");
        for (int i = 1; i <= n; i++) printf("%d ", arr[i]);
        printf("\n");
        shmdt(arr);
        _exit(0);
    }

    wait(NULL);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
