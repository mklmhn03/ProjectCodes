#ifndef DLLIST
#define DLLIST

#include <iostream>
using namespace std;


template<typename T>
class dllist{ //linked list of integers
    private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
            : data(data), prev(prev), next(next) {}
    };

    Node* head;
    Node* tail;
    int len;

    public:
    dllist() : head(nullptr), tail(nullptr), len(0) {}

    dllist(const dllist& rhs){
        head = nullptr;
        tail = head;
        for(int i = 0; i < rhs.size(); i++) {
            push(rhs.at(i));
        }   
        len = rhs.size();
    }

    ~dllist() {
        while(head != nullptr){
            Node* temp = head->next;
            delete head;
            head = temp;
        }
        len = 0;
    }
    
    void operator=(const dllist& rhs){
        // free the original list
        while(head != nullptr){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        
        // copy rhs list
        for(int i = 0; i < rhs.size(); i++) {
            push(rhs.at(i));
        }
        len = rhs.size();
    }
    


    void push(T data) {
        if(head == nullptr) {
            head = new Node(data, nullptr, nullptr);
            tail = head;
            len++;
            return;
        }
        tail->next = new Node(data, tail, nullptr);
        tail = tail->next;
        len++;
    }

    void pop() {
        if(head == nullptr) return; //0 elements
        if(tail == head) { //1 element
            head = nullptr;
            delete tail;
            tail = head;
            len--;
            return;
        }
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        len--;
    }
    
    int size() const {
        return len;
    }

    void print() const {
        for (Node* node = head; node != nullptr; node = node->next) {
            cout << node->data << " ";
        }
        cout << endl;
    }

    T& at(int idx) const {
        Node* currentNode = head;
        if (idx<0) return currentNode->prev->data;
        for (int i = 0; i<idx; i++) {
            currentNode = currentNode->next;
        }
        return currentNode->data;
    }

    void insert(T data, int index) {
        if (index == 0) {
            Node* nNode = new Node(data, nullptr, head);
            head = nNode;
            len++;
            return;
        }
        
        Node* currentNode = head;
        int i = 0;
        while(i<index-1) {
            currentNode = currentNode->next;
            i++;
        }

        
        len++;
        currentNode->next = new Node(data, currentNode, currentNode->next);
        if (index+1 == len) return;
        currentNode->next->next->prev = currentNode->next;
    }

    void remove(int index) {
        if (head == nullptr) return;
        if(index == 0) {
            Node* temp = head;
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
            delete temp;
            len--;
            return;
        }

        Node* currentNode = head;
        int i = 0;
        while(i<index) {
            currentNode = currentNode->next;
            i++;
        }

        currentNode->prev->next = currentNode->next;
        currentNode->next->prev = currentNode->prev;
        delete currentNode;
        len--;
    }
};

#endif //dllist