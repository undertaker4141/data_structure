#include <bits\stdc++.h>
using namespace std;

class NStack {
  public:
    NStack(int = 10);
    ~NStack();
    void Push(int d);
    int Pop();
    bool IsEmpty();
    void Output(NStack &s);
    // 列印參數 s 中所有的元素，列印完後，s中必須保留原有的元素並依
    // 原順序排好
    bool Remove(NStack &s, int num);
    // 移除根據給定的一個數字num，將 NStack中和num相等的數字移除；
    // 回傳true 表示移除成功，回傳false表示num不存在stack中
    // 移除過後，其他的元素仍須依原有的順序排好
    void Sort(NStack &s);
    // 將 stack s 中的元素由小到大排好序
  private:
    void Resize(); // 如 narray 的容量已滿，呼叫Resize()將陣列變原本的兩倍大小
    int top, size;
    int *narray;
};

NStack::NStack(int capacity) {
    if (capacity < 1)
        throw "Stack capacity must be > 0.";
    size = capacity;
    narray = new int[size];
    top = -1;
}

NStack::~NStack() { delete[] narray; }

void NStack::Resize() {
    int *newArray = new int[size * 2];
    copy(narray, narray + top, newArray);
    delete[] narray;
    narray = newArray;
    size *= 2;
}

inline bool NStack::IsEmpty() { return top == -1; }

void NStack::Push(int d) {
    if (top == size - 1)
        Resize();
    top++;
    narray[top] = d;
}

int NStack::Pop() {
    if (IsEmpty())
        throw "Stack is empty. Cannot delete.";
    return narray[top--];
}

void NStack::Output(NStack &s) {
    NStack tempStack(s.size);

    while (!s.IsEmpty())
        tempStack.Push(s.Pop());

    while (!tempStack.IsEmpty()) {
        int k = tempStack.Pop();
        cout << k << " ";
        s.Push(k);
    }

    cout << endl;
}

bool NStack::Remove(NStack &s, int num) {
    NStack tempStack(s.size);
    bool found = false;
    while (!s.IsEmpty())
        tempStack.Push(s.Pop());

    while (!tempStack.IsEmpty()) {
        int k = tempStack.Pop();
        if (k != num || found)
            s.Push(k);
        else if (!found)
            found = true;
    }
    return found;
}

void NStack::Sort(NStack &s) {
    NStack temp[s.top + 1];
    int len = s.top + 1;
    for (int i = 0; i < len; i++) {
        temp[i].Push(s.Pop());
    }
    for (int i = len - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            int m = temp[j].Pop();
            int n = temp[j + 1].Pop();
            if (m > n) {
                temp[j].Push(n);
                temp[j + 1].Push(m);
            } else {
                temp[j].Push(m);
                temp[j + 1].Push(n);
            }
        }
    }
    for (int i = 0; i < len; i++) {
        s.Push(temp[i].Pop());
    }
}

int main() {
    NStack nsteak;
    int n = 0;
    while (true) {
        cout << "Input a positive integer (-1 to end): ";
        cin >> n;
        if (n == -1)
            break;
        nsteak.Push(n);
    }
    int op = 0;
    while (op != 4) {
        cout << "Option: 1) Output. 2) Remove. 3) Sort. 4) Quit: ";
        cin >> op;
        switch (op) {
        case 1:
            nsteak.Output(nsteak);
            break;
        case 2: {
            int ref;
            cout << "Number to remove: ";
            cin >> ref;
            if (nsteak.Remove(nsteak, ref)) {
                cout << ref << " is deleted!" << endl;
                nsteak.Output(nsteak);
            } else
                cout << "Not found!" << endl;
            break;
        }
        case 3:
            nsteak.Sort(nsteak);
            nsteak.Output(nsteak);
            break;
        default:
            break;
        }
    }
    return 0;
}