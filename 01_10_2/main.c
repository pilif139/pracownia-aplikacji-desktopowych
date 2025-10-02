#include "linked_list.h"
#include "queue.h"
#include <stdio.h>

int main(void) {
    LinkedList* list = newLinkedList();
    push(list, 10);
    push(list, 20);
    pushFront(list, 5);
    for (int i = 0; i < list->size; i++) {
        Node* node = get(list, i);
        if (node != NULL) {
            printf("Element at index %d: %d\n", i, node->data);
        }
    }
    printf("Size of list: %d\n", list->size);
    pop(list);
    printf("Size of list after pop: %d\n", list->size);
    freeLinkedList(list);

    // kolejka
    Queue* q = initQueue();
    queue_push(q, 1);
    queue_push(q, 2);
    queue_push(q, 3);
    printf("Front element: %d\n", queue_front(q));
    for (int i=0; i<queue_getSize(q); i++) {
        printf("Element at index %d: %d\n", i, queue_get(q, i));
    }
    queue_pop(q);
    printf("Front element after pop: %d\n", queue_front(q));
    freeQueue(q);
    return 0;
}