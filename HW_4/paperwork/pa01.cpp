/*Let 𝑥 = (𝑥1,𝑥2,…,𝑥𝑛) and 𝑦 = (𝑦1,𝑦2,…,𝑦𝑚) be two chains. Write a C++ function to merge the 
two chains together to obtain the chain
 𝑧 =(𝑥1,𝑦1,𝑥2,𝑦2,…,𝑥𝑚,𝑦𝑚,𝑥𝑚+1,…,𝑥𝑛)       𝑖𝑓𝑚 ≤ 𝑛
 𝑎𝑛𝑑  𝑧 =(𝑦1,𝑥1,𝑦2,𝑥2,…,𝑦𝑛,𝑥𝑛,𝑦𝑛+1,…,𝑦𝑚)       𝑖𝑓𝑚 > 𝑛.
 Following the merge, x and y should represent empty chains because each node initially in x 
or y is now in z. No additional nodes may be used. What is the time complexity of your 
function?*/

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

void Chain::merge(Chain& x, Chain& y, Chain& z){
    if(x.size() >= y.size()){  // n >= m 的情況
        z.first = x.first;  // z 從 x 開始
        ChainNode* current_x = x.first;
        ChainNode* current_y = y.first;
        
        while(current_y != nullptr){  // 當 y 還有節點時進行交替連接
            // 保存下一個 x 節點
            ChainNode* next_x = current_x->next;
            // 保存下一個 y 節點
            ChainNode* next_y = current_y->next;
            
            // 連接順序：x -> y -> next_x
            current_x->next = current_y;
            current_y->next = next_x;
            
            // 移動指針
            current_x = next_x;
            current_y = next_y;
        }
        
        // x 和 y 清空
        x.first = nullptr;
        y.first = nullptr;
    }
    else{  // m > n 的情況
        z.first = y.first;  // z 從 y 開始
        ChainNode* current_x = x.first;
        ChainNode* current_y = y.first;
        
        while(current_x != nullptr){  // 當 x 還有節點時進行交替連接
            // 保存下一個 y 節點
            ChainNode* next_y = current_y->next;
            // 保存下一個 x 節點
            ChainNode* next_x = current_x->next;
            
            // 連接順序：y -> x -> next_y
            current_y->next = current_x;
            current_x->next = next_y;
            
            // 移動指針
            current_y = next_y;
            current_x = next_x;
        }
        
        // x 和 y 清空
        x.first = nullptr;
        y.first = nullptr;
    }
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
    x.insert(2);
    x.insert(3);
    x.insert(4);
    y.insert(5);
    y.insert(6);

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




