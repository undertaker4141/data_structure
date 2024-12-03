/*Implement a C++ template class for doubly linked 
circular lists with head node. You must include a constructor, copy constructor, 
and destructor as well as function to insert and delete. A bidirectional iterator 
must be included as well.*/


#include <iostream>
using namespace std;

template<class T>
class CircularList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value = T{}, Node* p = nullptr, Node* n = nullptr)
            : data(value), prev(p), next(n) {}
    };
    Node* head;  // 表頭節點
    int size;    // 串列大小

public:
    // 迭代器類別
    class iterator {
    private:
        Node* current;
        
    public:
        iterator(Node* node = nullptr) : current(node) {}
        
        T& operator*() { return current->data; }
        
        iterator& operator++() {
            current = current->next;
            return *this;
        }
        
        iterator& operator--() {
            current = current->prev;
            return *this;
        }
        
        bool operator==(const iterator& it) const {
            return current == it.current;
        }
        
        bool operator!=(const iterator& it) const {
            return current != it.current;
        }
        
        friend class CircularList;
    };

    // 建構子
    CircularList() {
        head = new Node();  // 建立表頭節點
        head->next = head;
        head->prev = head;
        size = 0;
    }
    
    // 複製建構子
    CircularList(const CircularList& other) : CircularList() {
        for (Node* curr = other.head->next; curr != other.head; curr = curr->next) {
            insert(end(), curr->data);
        }
    }
    
    // 解構子
    ~CircularList() {
        clear();
        delete head;
    }
    
    // 在迭代器位置前插入元素
    iterator insert(iterator pos, const T& value) {
        Node* newNode = new Node(value, pos.current->prev, pos.current);
        pos.current->prev->next = newNode;
        pos.current->prev = newNode;
        size++;
        return iterator(newNode);
    }
    
    // 刪除迭代器位置的元素
    iterator erase(iterator pos) {
        if (pos.current == head) return pos;
        
        Node* nextNode = pos.current->next;
        pos.current->prev->next = pos.current->next;
        pos.current->next->prev = pos.current->prev;
        delete pos.current;
        size--;
        return iterator(nextNode);
    }
    
    // 清空串列
    void clear() {
        while (!empty()) {
            erase(begin());
        }
    }
    
    // 判斷是否為空
    bool empty() const {
        return size == 0;
    }
    
    // 取得串列大小
    int getSize() const {
        return size;
    }
    
    // 迭代器相關函式
    iterator begin() { return iterator(head->next); }
    iterator end() { return iterator(head); }

    // 重載 << 運算子
    friend ostream& operator<<(ostream& os, const CircularList<T>& list) {
        Node* current = list.head->next;
        while (current != list.head) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

    // 在串列尾端插入元素
    void insert_back(const T& value) {
        insert(end(), value);
    }
};


int main()
{
    CircularList<int> list;

    // test insert
    list.insert_back(1);
    list.insert_back(2);
    list.insert_back(3);

    cout << "list: ";
    // traverse using iterator
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // test copy constructor
    CircularList<int> list2(list);
    cout << "list2 (copy of list): ";
    for (auto it = list2.begin(); it != list2.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // test erase
    list.erase(list.begin());
    cout << "list after erase first element: ";
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // test clear
    list2.clear();
    cout << "list2 after clear: ";
    for (auto it = list2.begin(); it != list2.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
