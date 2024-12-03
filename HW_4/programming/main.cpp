// Implement a C++ template class for doubly linked circular lists with head node.
//  You must include a constructor, copy constructor, and destructor as well as function to insert and delete.
//  A bidirectional iterator must be included as well.

#include <iostream>
using std::cout, std::endl;

template <typename T>
class CircularList
{
private:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
        Node(const T &d = T()) : data(d), prev(nullptr), next(nullptr) {}
    };
    Node *head;

public:
    // Bidirectional iterator
    class Iterator
    {
    private:
        Node *current;

    public:
        Iterator(Node *p = nullptr) : current(p) {}

        T &operator*() { return current->data; }

        Iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        Iterator &operator--()
        {
            current = current->prev;
            return *this;
        }

        bool operator==(const Iterator &other) const
        {
            return current == other.current;
        }

        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }

        friend class CircularList;
    };

    // 構造函數
    CircularList()
    {
        head = new Node();
        head->next = head;
        head->prev = head;
    }

    // copy constructor
    CircularList(const CircularList &other)
    {
        head = new Node();
        head->next = head;
        head->prev = head;

        for (Node *p = other.head->next; p != other.head; p = p->next)
        {
            insert_back(p->data);
        }
    }

    // destructor
    ~CircularList()
    {
        clear();
        delete head;
    }

    // insert at the back
    void insert_back(const T &value)
    {
        Node *newNode = new Node(value);
        newNode->prev = head->prev;
        newNode->next = head;
        head->prev->next = newNode;
        head->prev = newNode;
    }

    // erase the node at the specified iterator position
    void erase(Iterator pos)
    {
        if (pos.current != head)
        {
            Node *p = pos.current;
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
        }
    }

    // clear the list
    void clear()
    {
        Node *current = head->next;
        while (current != head)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
        head->next = head;
        head->prev = head;
    }

    // iterator related functions
    Iterator begin() { return Iterator(head->next); }
    Iterator end() { return Iterator(head); }
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
