/*Devise a linked representation for a list in which insertions and deletions can be made at 
either end in 𝑂(1) time. Such a structure is called a deque. Write functions to insert and 
delete at either end.*/

#include<iostream>
using namespace std;

// 定義節點結構
struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class Deque {
private:
    Node* front;
    Node* rear;

public:
    Deque() : front(nullptr), rear(nullptr) {}
    void insertFront(int value);
    void insertRear(int value);
    void deleteFront();
    void deleteRear();
    bool isEmpty();
    void display();
};
    // 在前端插入 O(1)
    void Deque::insertFront(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }

    }
    
    // 在後端插入 O(1)
    void Deque::insertRear(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
    }
    
    // 從前端刪除 O(1)
    void Deque::deleteFront() {
        if (isEmpty()) {
            cout << "Deque is empty!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front) {
            front->prev = nullptr;
        } else {
            rear = nullptr;
        }
        delete temp;

    }
    
    // 從後端刪除 O(1)
    void Deque::deleteRear() {
        if (isEmpty()) {
            cout << "Deque is empty!" << endl;
            return;
        }
        Node* temp = rear;
        rear = rear->prev;
        if (rear) {
            rear->next = nullptr;
        } else {
            front = nullptr;
        }
        delete temp;
    }
    
    // 檢查是否為空
    bool Deque::isEmpty() {
        return front == nullptr;
    }
    
    // 顯示所有元素
    void Deque::display() {
        Node* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }


int main() {
    Deque dq;
    
    dq.insertFront(10);
    dq.insertRear(20);
    dq.insertFront(5);
    dq.insertRear(30);
    
    cout << "Deque after insertions: ";
    dq.display();
    
    dq.deleteFront();
    dq.deleteRear();
    
    cout << "Deque after deletions: ";
    dq.display();
    
    return 0;
}

