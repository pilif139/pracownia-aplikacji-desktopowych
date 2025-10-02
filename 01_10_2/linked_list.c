#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

LinkedList* newLinkedList() {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void push(LinkedList* list, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

void pop(LinkedList* list) {
    if (list->head == NULL) return;
    if (list->head == list->tail) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    } else {
        Node* temp = list->head;
        while (temp->next != list->tail) {
            temp = temp->next;
        }
        free(list->tail);
        temp->next = NULL;
        list->tail = temp;
    }
    list->size--;
}

void pushFront(LinkedList* list, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    if (list->tail == NULL) {
        list->tail = newNode;
    }
    list->size++;
}

Node* get(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Index out of bounds\n");
        return NULL;
    }
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

void freeLinkedList(LinkedList* list) {
    Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}