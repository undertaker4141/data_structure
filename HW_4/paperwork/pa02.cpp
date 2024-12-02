/*Let 𝑥=(𝑥1,𝑥2,…,𝑥𝑛) and 𝑦=(𝑦1,𝑦2,…,𝑦𝑚) be two chains. Assume that in each chain, the 
nodes are in nondecreasing order of their data-field values. Write a C++ function to merge the 
two chains to obtain a new chain z in which the nodes are also in this order. Following the 
merge, x and y should represent empty chains because each node initially in x or y is now in z. 
No additional nodes may be used. What is the time complexity of your funciton?*/


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
        int size(); // 返回鏈結串列的元素個數
        void merge(Chain& x, Chain& y, Chain& z); // 合併兩個鏈結串列
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

int Chain::size(){
    int count = 0;
    ChainNode* current = first;
    while(current != nullptr){
        count++;
        current = current->next;
    }
    return count;
}

void Chain::merge(Chain& x, Chain& y, Chain& z) {
    ChainNode* current_x = x.first;
    ChainNode* current_y = y.first;
    
    // 初始化 z 的頭節點（選擇較小的值）
    if (current_x != nullptr && (current_y == nullptr || current_x->data <= current_y->data)) {
        z.first = current_x;
        current_x = current_x->next;
    } else if (current_y != nullptr) {
        z.first = current_y;
        current_y = current_y->next;
    } else {
        z.first = nullptr;
        return;
    }
    
    // current_z 用於追蹤 z 的當前節點
    ChainNode* current_z = z.first;
    
    // 合併兩個已排序的鏈表
    while (current_x != nullptr && current_y != nullptr) {
        if (current_x->data <= current_y->data) {
            current_z->next = current_x;
            current_x = current_x->next;
        } else {
            current_z->next = current_y;
            current_y = current_y->next;
        }
        current_z = current_z->next;
    }
    
    // 處理剩餘節點
    if (current_x != nullptr) {
        current_z->next = current_x;
    } else {
        current_z->next = current_y;
    }
    
    // 清空原始鏈表
    x.first = nullptr;
    y.first = nullptr;
}

void Chain::print(){
    ChainNode* current = first;
    while(current != nullptr){
        cout << current->data << " ";
        current = current->next;
    }
}

int main(){
    Chain x, y, z;
    x.insert(1);
    x.insert(3);
    x.insert(5);
    x.insert(7);
    x.insert(9);
    y.insert(2);
    y.insert(4);
    y.insert(6);
    y.insert(8);

    z.merge(x, y, z);
    cout << "x: ";
    x.print();
    cout << endl;
    cout << "y: ";
    y.print();
    cout << endl;
    cout << "z: ";
    z.print();
    cout << endl;
    return 0;
}






