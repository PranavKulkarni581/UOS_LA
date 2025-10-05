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

    printf("Calculator server running...\n");

    while (1) {
        if (calc->flag == 0) { // new request
            switch (calc->operator) {
                case '+': calc->result = calc->op1 + calc->op2; break;
                case '-': calc->result = calc->op1 - calc->op2; break;
                case '*': calc->result = calc->op1 * calc->op2; break;
                case '/': calc->result = (calc->op2 != 0) ? (double)calc->op1 / calc->op2 : 0; break;
                default: calc->result = 0; break;
            }
            calc->flag = 1; // result ready
        }
        usleep(100000); // small sleep to reduce CPU usage
    }

    shmdt(calc);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
