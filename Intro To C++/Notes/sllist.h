#ifndef SLLIST
#define SLLIST

#include <iostream>
using namespace std;


class sllist{ //linked list of integers
    private:
    Node* head;

    public:
    sllist() {
        Node* head = nullptr;
    }
    sllist(const sllist& rhs){
        head = nullptr;
        for(int i = 0; i < rhs.size(); i++) {
            push_back(rhs.at(i));
        }
    }

    ~sllist() {
        Node* curr;
        for (curr = head; head; curr = head) {
            head = head->next;
            delete curr;
        }
    }
    //Assignment constructor?
    void operator=(const sllist& rhs){
        // free the original list
        while(head != nullptr){
            Node* temp = head->next;
            delete head;
            head = temp;
        }
        // copy rhs list
        for(int i = 0; i < rhs.size(); i++) {
            push_back(rhs.at(i));
        }
    }
    


    void push_back(int data) {
        if(head == nullptr) {
            head = new Node;
            head->data = data;
            head->next = nullptr;
            return;
        }
        Node* currentNode = head;
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        currentNode->next = new Node;
        currentNode->next->next = nullptr;
        currentNode->next->data = data;
    }

    int pop_back() const {
        if(head == nullptr) {
            head = new Node;
            head->data = data;
            head->next = nullptr;
            return NULL;
        }
        Node* currentNode = head;
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        return currentNode->data;
    }
    int at(int index) const {
        Node* currentNode = head;
        int i = 0;
        while(i<index) {
            currentNode = currentNode->next;
            i++;
        }
        return currentNode->data;
    }
    int size() const {
        if(head == nullptr) return 0;
        Node* currentNode = head;
        int i = 1;
        while(currentNode->next != nullptr) {
            currentNode = currentNode->next;
            i++;
        }
        return i;
    }
    void insert(int data, int index) {
        if (index == 0) {
            Node* nNode = new Node;
            nNode->data = data;
            nNode->next = head;
            head = currentNode;
            return;
        }

        Node* currentNode = head;
        int i = 0;
        while(i<index-1) {
            currentNode = currentNode->next;
            i++;
        }

        Node* afterNode = currentNode->next;
        currentNode->next = new Node;
        currentNode->next->data = data;
        currentNode->next->next = afterNode;
    }
    void remove(int index) {
        Node* currentNode = head;
        int i = 1;
        while(i<index) {
            if (currentNode == nullptr) return;
            currentNode = currentNode->next;
            i++;
        }

        if (currentnode == head) {
            head = currentNode->next;
            delete currentNode;
            return;
        }
        Node* afterNode = currentNode->next;
        currentNode->next = currentNode->next->next;
        delete afterNode;
    }
}

#endif //sllist