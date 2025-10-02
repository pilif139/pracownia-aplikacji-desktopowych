#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue* initQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->head = -1;
    q->tail = 0;
    return q;
}

void freeQueue(Queue *q) {
    free(q);
}

int queue_front(Queue *q) {
    if (queue_isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->items[q->head + 1];
}

int queue_isEmpty(Queue *q) {
    return q->head == q->tail - 1;
}

int queue_isFull(Queue *q) {
    return q->tail ==  MAX_QUEUE_SIZE;
}

int queue_getSize(Queue *q) {
    return q->tail - q->head - 1;
}

int queue_get(Queue *q, int index) {
    return q->items[index];
}

void queue_push(Queue* q, int value) {
    if (queue_isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    q->items[q->tail] = value;
    q->tail++;
}

void queue_pop(Queue* q) {
    if (queue_isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    q->head++;
}