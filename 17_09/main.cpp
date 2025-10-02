#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;
};

int main() {
    int a;
    int* b;
    int tab[10];
    std::cout<<&a<<" ->"<<a<<std::endl;
    std::cout<<&b<<" ->"<<b<<std::endl;
    std::cout<<"Tablica: "<<&tab<<"; Wartość: "<<tab<<std::endl;
    b = new int[10];
    b[0] = 10;
    std::cout<<"Tablica z new int[10]: "<<&b<<"; Wartość: "<<b<<std::endl;
    for (int i=0; i<10; i++) {
        std::cout<<"Adres b["<<i<<"]: "<<&b[i]<<"; Wartość: "<<b[i]<<std::endl;
    }
    for (int i=0; i<10; i++) {
        std::cout<<*(b+i)<<std::endl;
    }
    /* zadanie domowe:
     * - poodczytywać wszystko to w debugerze,
     * - zaalokować tablice i poodczytywać
     * - zaalokować dynamicznie
     * - stworzyć linked list (struct)
     * -
     **/

    Node<int>* head = new Node<int>{1, nullptr};
    head->next = new Node<int>{2, nullptr};
    head->next->next = new Node<int>{3, nullptr};

    Node<int>* current = head;
    while (current != nullptr) {
        std::cout << "Node data: " << current->data << std::endl;
        current = current->next;
    }

    current = head;
    while (current != nullptr) {
        Node<int>* next = current->next;
        delete current;
        current = next;
    }

    return 0;
}