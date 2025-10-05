#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "job_common.h"

unsigned long long factorial(int n) {
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) fact *= i;
    return fact;
}

unsigned long long fibonacci(int n) {
    if (n <= 1) return n;
    unsigned long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i*i <= n; i++) if (n % i == 0) return 0;
    return 1;
}

int main() {
    int jobqid = msgget(JOB_QUEUE_KEY, 0666 | IPC_CREAT);
    int resqid = msgget(RESULT_QUEUE_KEY, 0666 | IPC_CREAT);

    struct job_msg job;
    struct result_msg res;

    printf("Server started...\n");

    while (1) {
        msgrcv(jobqid, &job, sizeof(job)-sizeof(long), 0, 0);

        res.mtype = 1;
        if (job.job_type == JOB_TYPE_FACTORIAL) {
            sprintf(res.result, "Factorial of %d = %llu", job.data, factorial(job.data));
        } else if (job.job_type == JOB_TYPE_FIBONACCI) {
            sprintf(res.result, "Fibonacci of %d = %llu", job.data, fibonacci(job.data));
        } else if (job.job_type == JOB_TYPE_PRIME) {
            sprintf(res.result, "%d is %s", job.data, isPrime(job.data) ? "Prime" : "Not Prime");
        }

        msgsnd(resqid, &res, sizeof(res)-sizeof(long), 0);
    }

    return 0;
}
