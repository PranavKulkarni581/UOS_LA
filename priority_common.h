#define PRIORITY_QUEUE_KEY 4321
#define MSG_SIZE 256

struct priority_msg {
    long mtype;         // Priority (higher value = higher priority)
    char text[MSG_SIZE]; // Message text
};
