#define JOB_QUEUE_KEY 1234
#define RESULT_QUEUE_KEY 5678

#define JOB_TYPE_FACTORIAL 1
#define JOB_TYPE_FIBONACCI 2
#define JOB_TYPE_PRIME 3

struct job_msg {
    long mtype;
    int job_type;
    int data;
};

struct result_msg {
    long mtype;
    char result[100];
};
