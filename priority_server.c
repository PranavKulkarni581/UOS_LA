#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "priority_common.h"

int main() {
    int qid = msgget(PRIORITY_QUEUE_KEY, 0666 | IPC_CREAT);
    struct priority_msg msg;

    printf("Priority Server started...\n");

    while (1) {
        // Receive the highest priority message (use 0 to pick highest mtype)
        msgrcv(qid, &msg, sizeof(msg.text), 0, 0);
        printf("Received [Priority %ld]: %s\n", msg.mtype, msg.text);
    }

    return 0;
}
