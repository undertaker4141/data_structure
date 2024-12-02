/*Let 𝑥1,𝑥2,…,𝑥𝑛 be the elements of a chain. Each 𝑥𝑖 is an integer. Write a C++ function to 
compute the expression ∑ 𝑥𝑖∗𝑥𝑖+5 𝑛−5
 𝑖=1 . [Hint: use two iterators to simultaneously traverse the 
chain.]*/


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
        ChainNode* first;
    public:
        Chain();
        void insert(int value); // 插入元素
        void print(); // 打印鏈結串列
        int computeSum(); // 計算 ∑(xi * xi+5)
};

Chain::Chain(){
    first = nullptr;
}

void Chain::insert(int value){
    ChainNode* newNode = new ChainNode{value, nullptr}; 
    if(first == nullptr){
        first = newNode;
    }
    else{
        ChainNode* current = first;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = newNode;
    }
}


void Chain::print(){
    ChainNode* current = first;
    while(current != nullptr){
        cout << current->data << " ";
        current = current->next;
    }
}

int Chain::computeSum() {
    int sum = 0;
    ChainNode* current_1 = first;
    ChainNode* current_2 = first;
    
    // 將 current_2 指針向後移動 5 個位置
    for (int i = 0; i < 5; i++) {
        if (current_2 == nullptr) return 0; // 如果鏈表長度小於 5，返回 0
        current_2 = current_2->next;
    }
    
    // 同時使用兩個指針遍歷鏈表
    while (current_2 != nullptr) {
        sum += current_1->data * current_2->data;
        current_1 = current_1->next;
        current_2 = current_2->next;
    }
    
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






