#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

struct msgbuf {
    long mtype;
    int num;
};

int main() {
    key_t key = ftok(".", 'N');
    int qid = msgget(key, IPC_CREAT | 0666);
    pid_t pid = fork();

    if (pid > 0) {
        struct msgbuf sb;
        sb.mtype = 1;
        int n;
        printf("Enter numbers (0 to stop): ");
        while (1) {
            scanf("%d", &n);
            sb.num = n;
            msgsnd(qid, &sb, sizeof(int), 0);
            if (n == 0) break;
        }
        wait(NULL);
        msgctl(qid, IPC_RMID, NULL);
    } else {
        struct msgbuf rb;
        int sum = 0;
        while (1) {
            msgrcv(qid, &rb, sizeof(int), 1, 0);
            if (rb.num == 0) break;
            sum += rb.num;
        }
        printf("Sum = %d\n", sum);
        _exit(0);
    }
    return 0;
}
