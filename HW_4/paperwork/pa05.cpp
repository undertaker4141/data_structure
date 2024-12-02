/*Do Exercise 1 of Section 4.3 for the case of circularly linked lists.*/


#include<iostream>
using namespace std;

template<class T>
class Chain{
    private:
        class ChainNode{
            public:
                T data;
                ChainNode* next;
                ChainNode(T value, ChainNode* next = nullptr)
                    : data(value), next(next) {}
        };
        ChainNode* last;
    public:
        Chain();
        void insert(T value); // 插入元素
        // 重載 << 運算子
        template<class U>
        friend ostream& operator<<(ostream& os, const Chain<U>& chain);
};

template<class T>
Chain<T>::Chain(){
    last = nullptr;
}

template<class T>
void Chain<T>::insert(T value){
    ChainNode* newNode = new ChainNode{value}; 
    if(last == nullptr){
        last = newNode;
        last->next = last;//指向自己形成循環
    }
    else{
        newNode->next = last->next; //指向第一個節點
        last->next = newNode; //指向新節點
        last = newNode; //更新最後一個節點
    }
}

// 重載 << 運算子
template<class T>
ostream& operator<<(ostream& os, const Chain<T>& chain){
    if (chain.last == nullptr) return os;
    
    class Chain<T>::ChainNode* current = chain.last->next; //指向第一個節點
    do {
        os << current->data << " ";
        current = current->next;
    } while(current != chain.last->next); // 使用 do-while 確保至少輸出一次(節點只有一個的時候還是會輸出)
    
    return os;
}

int main(){
    Chain<int> x;
    Chain<char> y;
    x.insert(1);
    x.insert(2);
    x.insert(3);
    x.insert(4);
    y.insert('a');
    y.insert('b');
    y.insert('c');
    cout << x << endl;
    cout << y << endl;
    return 0;
}
