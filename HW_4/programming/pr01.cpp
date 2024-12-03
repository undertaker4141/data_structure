/*Implement a C++ template class for doubly linked 
circular lists with head node. You must include a constructor, copy constructor, 
and destructor as well as function to insert and delete. A bidirectional iterator 
must be included as well.*/

#include <iostream>
using namespace std;

template<class T>
class CircularList {
private:
    struct Node {//建立DB_Circular_List的節點
        T data;
        Node* prev;//前一個節點
        Node* next;//下一個節點
        Node(const T& value = T{}, Node* p = nullptr, Node* n = nullptr)//建構子
            : data(value), prev(p), next(n) {}
    };
    Node* head;//表頭節點
    int size;//串列大小

public:
    // 迭代器類別
    class iterator {
    private:
        Node* current;//表當前節點
        
    public:
        iterator(Node* node = nullptr);//建構子
        T& operator*();//參考
        iterator& operator++();//遞增
        iterator& operator--();//遞減
        bool operator==(const iterator& it) const;//相等
        bool operator!=(const iterator& it) const;//不相等
        
        friend class CircularList;//友類別
    };

    // 建構子和解構子
    CircularList();//建構子
    CircularList(const CircularList& other);//複製建構子
    ~CircularList();//解構子
    
    // 操作方法
    iterator insert(iterator pos, const T& value);//插入
    iterator erase(iterator pos);//刪除
    void clear();//清除
    bool empty() const;//是否為空
    int getSize() const;//取得大小
    void insert_back(const T& value);//插入(尾端)
    
    // 迭代器相關
    iterator begin();//開始
    iterator end();//結束
    
    // 運算子重載
    friend ostream& operator<<(ostream& os, const CircularList<T>& list);
};

// 迭代器方法實作
template<class T>
CircularList<T>::iterator::iterator(Node* node) : current(node) {}

template<class T>
T& CircularList<T>::iterator::operator*() { 
    return current->data; 
}

template<class T>
typename CircularList<T>::iterator& CircularList<T>::iterator::operator++() {
    current = current->next;
    return *this;
}

template<class T>
typename CircularList<T>::iterator& CircularList<T>::iterator::operator--() {
    current = current->prev;
    return *this;
}

template<class T>
bool CircularList<T>::iterator::operator==(const iterator& it) const {
    return current == it.current;
}

template<class T>
bool CircularList<T>::iterator::operator!=(const iterator& it) const {
    return current != it.current;
}

// CircularList 方法實作
template<class T>
CircularList<T>::CircularList() {//dummy head 建構子
    head = new Node();
    head->next = head;
    head->prev = head;
    size = 0;
}

template<class T>
CircularList<T>::CircularList(const CircularList& other) : CircularList() {//複製建構子
    for (Node* curr = other.head->next; curr != other.head; curr = curr->next) {
        insert(end(), curr->data);
    }
}

template<class T>
CircularList<T>::~CircularList() {//解構子
    clear();
    delete head;
}

template<class T>
typename CircularList<T>::iterator CircularList<T>::insert(iterator pos, const T& value) {//插入
    Node* newNode = new Node(value, pos.current->prev, pos.current);
    pos.current->prev->next = newNode;
    pos.current->prev = newNode;
    size++;
    return iterator(newNode);
}

template<class T>
typename CircularList<T>::iterator CircularList<T>::erase(iterator pos) {//刪除
    if (pos.current == head) return pos;
    Node* nextNode = pos.current->next;
    pos.current->prev->next = pos.current->next;
    pos.current->next->prev = pos.current->prev;
    delete pos.current;
    size--;
    return iterator(nextNode);
}

template<class T>
void CircularList<T>::clear() {//清除
    while (!empty()) {
        erase(begin());
    }
}

template<class T>
bool CircularList<T>::empty() const {//是否為空 
    return size == 0;
}

template<class T>
int CircularList<T>::getSize() const {//取得大小
    return size;
}

template<class T>
void CircularList<T>::insert_back(const T& value) {//插入(尾端)
    insert(end(), value);
}

template<class T>
typename CircularList<T>::iterator CircularList<T>::begin() {//開始
    return iterator(head->next);
}

template<class T>
typename CircularList<T>::iterator CircularList<T>::end() {//結束
    return iterator(head);
}

template<class T>
ostream& operator<<(ostream& os, const CircularList<T>& list) {//輸出
    typename CircularList<T>::Node* current = list.head->next;
    while (current != list.head) {
        os << current->data << " ";
        current = current->next;
    }
    return os;
}

int main() {
    CircularList<int> list;

    // test insert
    list.insert_back(2);
    list.insert_back(4);
    list.insert_back(8);
    list.insert_back(6);
    list.insert_back(4);

    cout << "list: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // test copy constructor
    CircularList<int> list2(list);
    cout << "list2 (copy of list): ";
    for (auto it = list2.begin(); it != list2.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // test erase
    list.erase(list.begin());
    cout << "list after erase first element: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    //test insert
    list.insert(++list.begin(), 1);
    cout << "list after insert 2 at beginning: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // test clear
    list2.clear();
    cout << "list2 after clear: ";
    for (auto it = list2.begin(); it != list2.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
