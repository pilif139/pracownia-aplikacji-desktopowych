#ifndef INC_01_10_2025_LINKEDLIST_H
#define INC_01_10_2025_LINKEDLIST_H

template<typename T>
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

template<typename T>
class LinkedList {
public:
    void push(T data);
    void pop();
    int getSize();
private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    int listSize = 0;
};


#endif