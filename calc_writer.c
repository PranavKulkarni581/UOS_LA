#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

struct calc_shm {
    int op1;
    int op2;
    char operator;
    double result;
    int flag; // 0 = request ready, 1 = result ready
};

int main() {
    key_t key = ftok(".", 'C');
    int shmid = shmget(key, sizeof(struct calc_shm), 0666 | IPC_CREAT);
    struct calc_shm *calc = (struct calc_shm*) shmat(shmid, NULL, 0);

    printf("Enter operand1: ");
    scanf("%d", &calc->op1);
    printf("Enter operand2: ");
    scanf("%d", &calc->op2);
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &calc->operator);

    calc->flag = 0; // request ready

    // wait for result
    while (calc->flag == 0) sleep(1);

    printf("Result: %.2lf\n", calc->result);

    shmdt(calc);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
