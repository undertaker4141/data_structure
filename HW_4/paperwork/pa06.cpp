/*Do Exercise 4 of Section 4.3 for the case of circularly linked lists.*/


#include<iostream>
using namespace std;


class Chain{
    private:
        class ChainNode{
            public:
                int data;
                ChainNode* next;
                ChainNode(int value, ChainNode* next = nullptr)
                    : data(value), next(next) {}
        };
        ChainNode* last;
    public:
        Chain();
        void insert(int value); // 插入元素
        void print(); // 打印鏈結串列
        int computeSum(); // 計算 ∑(xi * xi+5)
};

Chain::Chain(){
    last = nullptr;
}

void Chain::insert(int value){
    ChainNode* newNode = new ChainNode(value);
    if (last == nullptr) {
        newNode->next = newNode; // 指向自己
        last = newNode;
    } else {
        newNode->next = last->next; // 新節點指向第一個節點
        last->next = newNode; // 原本的最後節點指向新節點
        last = newNode; // 更新最後節點
    }
}

void Chain::print(){
    if (last == nullptr) return;
    ChainNode* current = last->next; // 從第一個節點開始
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != last->next);
}

int Chain::computeSum() {
    if (last == nullptr) return 0;
    int sum = 0;
    ChainNode* current_1 = last->next; // 從第一個節點開始
    ChainNode* current_2 = last->next;
    
    // 將 current_2 指針向前移動 5 個位置
    for (int i = 0; i < 5; i++) {
        if (current_2 == last->next && i != 0) return 0; // 如果鏈表長度小於 5，返回 0
        current_2 = current_2->next;
    }
    // 計算總和，直到 current_2 回到第一個節點
    do {
        sum += current_1->data * current_2->data;
        current_1 = current_1->next;
        current_2 = current_2->next;
    } while (current_2 != last->next);
    
    return sum;
}

int main(){

    Chain test;
    test.insert(1);
    test.insert(2);
    test.insert(3);
    test.insert(4);
    test.insert(5);
    test.insert(6);
    test.insert(5);
    test.insert(4);
    test.insert(3);
    test.insert(2);
    test.insert(1);
    cout << "Sum of xi * x(i+5): " << test.computeSum() << endl;
    return 0;
}






