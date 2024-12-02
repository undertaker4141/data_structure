/*Write a C++ template function to output all elements of a chain by overloading the output 
operator <<. Assume that the operator << has been overloaded for the data type T.*/

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
        ChainNode* first;
    public:
        Chain();
        void insert(T value); // 插入元素
        // 重載 << 運算子
        template<class U>
        friend ostream& operator<<(ostream& os, const Chain<U>& chain);
};

template<class T>
Chain<T>::Chain(){
    first = nullptr;
}

template<class T>
void Chain<T>::insert(T value){
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

// 重載 << 運算子
template<class T>
ostream& operator<<(ostream& os, const Chain<T>& chain){
    class Chain<T>::ChainNode* current = chain.first;
    while(current != nullptr){
        os << current->data << " ";
        current = current->next;
    }
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
