/*A matrix is a rectangular array of numbers. When the number of rows and the 
number of columns of a matrix are the same, we called the matrix a square 
matrix. Implement the below Matrix ADT that is extended from ADT 2.4 in page 
97 in C++.*/

#include <bits/stdc++.h>
using namespace std;

class Matrix{
    private:
    struct Element {
        int row;
        int col;
        int value;
    };
    
    int rows, cols;  // 矩陣的行數和列數
    vector<Element> elements;  // 儲存非零元素的向量
    int capacity;//最大元素數量

    public:

/*題目要的方法*/
    Matrix(int row,int cols,int t);
    // 建構子函式，建立一個有 r 列 c 行並且具有放 t 個非零項的容量
    Matrix Transpose();
    //回傳將 *this 中每個三元組的行與列交換後的 Matrix轉置
    Matrix Add(Matrix b);
    // 如果 *this 和 b 的維度一樣，那麼就把相對應的項給相加
    // 亦即，具有相同列和行的值會被回傳；否則的話丟出例外。
    Matrix Multiply(Matrix b);
    // 如果*this 中的行數和 b 中的列數一樣多的話，那麼回傳的矩陣 d 就是 *this 和 b
    //（依據 d[i][j]=Σ(a[i][k]．b[k][j]，其中 d[i][j]是第 (i, j) 個元素）相乘的結果。k 的範
    // 圍 從 0 到*this 的行數減 1；如果不一樣多的話，那麼就丟出例外。
    int Determinant( );
    // 如果*this 是一個 square matrix，回傳𝑑𝑒𝑡(𝐴).
    int Adjoint( );
    // 如果*this 是一個 square matrix，回傳 adj(A).
    Matrix Inverse ( );
    // 如果*this 是一個 square matrix，回傳A反函數
    Matrix Cofactor ( );
    // 如果*this 是一個 square matrix，回傳𝐴𝑖𝑗.

/*額外自己定義的方法*/
    void addElement(int row, int col, int value);
};
Matrix::Matrix(int rows,int cols,int t){
    this->rows = rows;
    this->cols = cols;
    capacity = t;
    elements.reserve(capacity);
}

void Matrix::addElement(int row, int col, int value){
    if (row >= rows || col >= cols)
            throw out_of_range("Invalid position");
    if (elements.size() >= capacity)
            throw overflow_error("capacity overflow");

        for (auto &elem : elements) {
            if (elem.row == row && elem.col == col) {
                elem.value = value;
                return;
            }
        }
        elements.emplace_back(row, col, value);
        sort(elements.begin(), elements.end());
}

Matrix Matrix::Transpose(){
    Matrix result(cols, rows, capacity);
        for (const auto &elem : elements) {
            result.addElement(elem.col, elem.row, elem.value);
        }
        return result;
}



int main()
{
    return 0;
}
