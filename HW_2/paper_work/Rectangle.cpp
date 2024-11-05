// Overload operator< for class Rectangle such that r < s if and only if the area of r is less than that of s.

#include <bits/stdc++.h>
using namespace std;
class Rectangle//參考課本，有些沒用到的methods就沒有細寫
{
public:
    // methods
    Rectangle(int xLow, int yLow, int height, int width);
    ~Rectangle() {}
    int GetHeight() const;
    int GetWidth() const;
    int Area() const;
    bool operator<(const Rectangle &s);
    bool operator==(const Rectangle &s);
    bool operator>(const Rectangle &s);
    private:
        int xLow;
        int yLow;
        int height;
        int width;
};
Rectangle::Rectangle(int xLow = 0, int yLow = 0, int height = 0, int width = 0){
    this->xLow = xLow;
    this->yLow = yLow;
    this->height = height;
    this->width = width;
}
int Rectangle::Area() const
{
    return height * width;
}

bool Rectangle::operator<(const Rectangle &s)
{
    return (this->Area()) < (s.Area());
}

int main()
{
    Rectangle a(0, 0, 5, 6), b(0, 0, 6, 6);
    Rectangle c(0, 0, 11, 20), d(0, 0, 10, 20);
    cout << "overload < example(test)--ture:" <<endl;
    // <
    cout << "a(0, 0, 10, 20), b(0, 0, 11, 20)" <<endl;
    cout << "result: " <<"bool(a < b) : "<<bool(a < b) <<endl;

    cout << endl;

    cout << "overload < example(test)--false:" <<endl;
    // 其他(>，=)(以>作範例)
    cout << "c(0, 0, 10, 20), d(0, 0, 9, 20)" <<endl;
    cout << "result: " <<"bool(c < d) : "<<bool(c < d) <<endl;
}
