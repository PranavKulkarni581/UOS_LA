#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGLEN 256

struct msgbuf {
    long mtype;
    char mtext[MSGLEN];
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [1|2]\n", argv[0]);
        printf("Run one terminal with '1' and another with '2'\n");
        return 1;
    }

    key_t key = ftok(".", 'C');
    int qid = msgget(key, IPC_CREAT | 0666);

    int self = atoi(argv[1]);
    int other = (self == 1) ? 2 : 1;

    struct msgbuf sb, rb;

    printf("Chat started. Type 'exit' to quit.\n");

    if (self == 1) {
        while (1) {
            if (msgrcv(qid, &rb, MSGLEN, other, IPC_NOWAIT) > 0) {
                printf("User %d: %s\n", other, rb.mtext);
                if (strcmp(rb.mtext, "exit") == 0) break;
            }

            printf("You: ");
            fflush(stdout);
            if (fgets(sb.mtext, MSGLEN, stdin) == NULL) break;
            sb.mtext[strcspn(sb.mtext, "\n")] = 0;
            sb.mtype = self;
            msgsnd(qid, &sb, strlen(sb.mtext) + 1, 0);
            if (strcmp(sb.mtext, "exit") == 0) break;
        }
    } else {
        while (1) {
            if (msgrcv(qid, &rb, MSGLEN, other, IPC_NOWAIT) > 0) {
                printf("User %d: %s\n", other, rb.mtext);
                if (strcmp(rb.mtext, "exit") == 0) break;
            }

            printf("You: ");
            fflush(stdout);
            if (fgets(sb.mtext, MSGLEN, stdin) == NULL) break;
            sb.mtext[strcspn(sb.mtext, "\n")] = 0;
            sb.mtype = self;
            msgsnd(qid, &sb, strlen(sb.mtext) + 1, 0);
            if (strcmp(sb.mtext, "exit") == 0) break;
        }
    }

    if (self == 1) msgctl(qid, IPC_RMID, NULL);
    return 0;
}
    