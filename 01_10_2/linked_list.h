#ifndef INC_01_10_2_LINKED_LIST_H
#define INC_01_10_2_LINKED_LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

LinkedList* newLinkedList();
void push(LinkedList* list, int data);
void pop(LinkedList* list);
void pushFront(LinkedList* list, int data);
Node* get(LinkedList* list, int index);
void freeLinkedList(LinkedList* list);


#endif //INC_01_10_2_LINKED_LIST_H