#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "job_common.h"

int main() {
    int jobqid = msgget(JOB_QUEUE_KEY, 0666);
    int resqid = msgget(RESULT_QUEUE_KEY, 0666);

    struct job_msg job;
    struct result_msg res;

    int choice, num;
    printf("Job Scheduling Client\n");
    printf("1. Factorial\n2. Fibonacci\n3. Prime check\nChoice: ");
    scanf("%d", &choice);
    printf("Enter number: ");
    scanf("%d", &num);

    job.mtype = 1;
    job.job_type = choice;
    job.data = num;

    msgsnd(jobqid, &job, sizeof(job)-sizeof(long), 0);

    msgrcv(resqid, &res, sizeof(res)-sizeof(long), 0, 0);
    printf("Result from server: %s\n", res.result);

    return 0;
}
