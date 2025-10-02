template<typename T>
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

template<typename T>
class LinkedList {
    Node<T> *head;
    Node<T> *tail;
    int size = 0;
public:
    void push(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void pop() {
        if (head == nullptr) return;
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            *head = *(head->next);
        }
        size--;
    };

    int getSize() {
        return size;
    }
};