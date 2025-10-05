#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "priority_common.h"

int main() {
    int qid = msgget(PRIORITY_QUEUE_KEY, 0666);
    struct priority_msg msg;

    long priority;
    char text[MSG_SIZE];

    printf("Enter message priority (higher number = higher priority): ");
    scanf("%ld", &priority);
    getchar(); // consume newline
    printf("Enter message text: ");
    fgets(text, MSG_SIZE, stdin);
    text[strcspn(text, "\n")] = 0;

    msg.mtype = priority;
    strcpy(msg.text, text);

    msgsnd(qid, &msg, sizeof(msg.text), 0);
    printf("Message sent!\n");

    return 0;
}
