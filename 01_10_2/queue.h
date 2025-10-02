#ifndef INC_01_10_2_QUEUE_H
#define INC_01_10_2_QUEUE_H
#define MAX_QUEUE_SIZE 100

typedef struct {
    int items[MAX_QUEUE_SIZE];
    int head;
    int tail;
} Queue;

void queue_push(Queue *q, int value);
void queue_pop(Queue *q);
int queue_front(Queue *q);
int queue_isEmpty(Queue *q);
int queue_isFull(Queue *q);
int queue_getSize(Queue *q);
int queue_get(Queue *q, int index);
Queue* initQueue();
void freeQueue(Queue *q);

#endif