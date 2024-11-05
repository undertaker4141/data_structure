/*A matrix is a rectangular array of numbers. When the number of rows and the
number of columns of a matrix are the same, we called the matrix a square
matrix. Implement the below Matrix ADT that is extended from ADT 2.4 in page
97 in C++.*/

#include <bits/stdc++.h>
using namespace std;

class Matrix {
  private:
    struct Element {
        int row;
        int col;
        int value;
        Element(int r, int c, int v) : row(r), col(c), value(v) {}
        bool operator<(const Element &other) const {
            if (row != other.row)
                return row < other.row;
            return col < other.col;
        }
    };

    int rows, cols;           // 矩陣的行數和列數
    vector<Element> elements; // 儲存非零元素的向量
    int capacity;             // 最大元素數量

  public:
    /*題目要的方法*/
    Matrix(int row, int cols, int t);
    // 建構子函式，建立一個有 r 列 c 行並且具有放 t 個非零項的容量
    Matrix Transpose();
    // 回傳將 *this 中每個三元組的行與列交換後的 Matrix轉置
    Matrix Add(Matrix b);
    // 如果 *this 和 b 的維度一樣，那麼就把相對應的項給相加
    // 亦即，具有相同列和行的值會被回傳；否則的話丟出例外。
    Matrix Multiply(Matrix b);
    // 如果*this 中的行數和 b 中的列數一樣多的話，那麼回傳的矩陣 d 就是 *this 和
    // b
    // （依據 d[i][j]=Σ(a[i][k]．b[k][j]，其中 d[i][j]是第 (i, j)
    // 個元素）相乘的結果。k 的範
    // 圍 從 0 到*this 的行數減 1；如果不一樣多的話，那麼就丟出例外。
    int Determinant();
    // 如果*this 是一個 square matrix，回傳𝑑𝑒𝑡(𝐴).
    Matrix Adjoint();
    // 如果*this 是一個 square matrix，回傳 adj(A).
    Matrix Inverse();
    // 如果*this 是一個 square matrix，回傳A反函數
    Matrix Cofactor();
    // 如果*this 是一個 square matrix，回傳𝐴𝑖𝑗.

    /*額外自己定義的方法*/
    // 新增元素
    void addElement(int row, int col, int value);
    // 取得指定位置的值，若無則返回 0
    int getValue(int row, int col) const;
    // 計算此矩陣排除指定列和行的 minor 矩陣
    Matrix getMinor(int excludeRow, int excludeCol);
    // 計算代數餘因子
    int getAlgebraicCofactor(int i, int j);
    // 顯示矩陣
    void Display();
};

/*實作題目要求之方法*/
Matrix::Matrix(int rows, int cols, int t) {
    this->rows = rows;
    this->cols = cols;
    capacity = t;
    elements.reserve(capacity);
}

Matrix Matrix::Transpose() {
    Matrix result(cols, rows, capacity);
    for (const auto &elem : elements) {
        result.addElement(elem.col, elem.row, elem.value);
    }
    return result;
}

Matrix Matrix::Add(Matrix b) {
    if (rows != b.rows || cols != b.cols)
        throw invalid_argument("Dimension mismatch");

    Matrix result(rows, cols, capacity + b.capacity);
    size_t i = 0, j = 0;

    while (i < elements.size() && j < b.elements.size()) {
        if (elements[i].row < b.elements[j].row ||
            (elements[i].row == b.elements[j].row &&
             elements[i].col < b.elements[j].col)) {
            result.addElement(elements[i].row, elements[i].col,
                              elements[i].value);
            ++i;
        } else if (elements[i].row > b.elements[j].row ||
                   (elements[i].row == b.elements[j].row &&
                    elements[i].col > b.elements[j].col)) {
            result.addElement(b.elements[j].row, b.elements[j].col,
                              b.elements[j].value);
            ++j;
        } else {
            int sum = elements[i].value + b.elements[j].value;
            if (sum != 0)
                result.addElement(elements[i].row, elements[i].col, sum);
            ++i;
            ++j;
        }
    }

    while (i < elements.size()) {
        result.addElement(elements[i].row, elements[i].col,
                          elements[i].value++);
        i++;
    }
    while (j < b.elements.size()) {
        result.addElement(b.elements[j].row, b.elements[j].col,
                          b.elements[j].value++);
        j++;
    }

    return result;
}

Matrix Matrix::Multiply(Matrix b) {
    if (cols != b.rows)
        throw invalid_argument("Dimension mismatch for multiplication");

    Matrix result(rows, b.cols, rows * b.cols);
    Matrix otherT = b.Transpose();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < b.cols; ++j) {
            int sum = 0;
            for (const auto &elem : elements) {
                if (elem.row == i) {
                    for (const auto &otherElem : otherT.elements) {
                        if (otherElem.row == j && otherElem.col == elem.col) {
                            sum += elem.value * otherElem.value;
                        }
                    }
                }
            }
            if (sum != 0)
                result.addElement(i, j, sum);
        }
    }
    return result;
}

int Matrix::Determinant() {
    if (rows != cols) {
        throw invalid_argument("not square matrix");
    }

    if (rows == 1) {
        return getValue(0, 0);
    }

    if (rows == 2) {
        return getValue(0, 0) * getValue(1, 1) -
               getValue(0, 1) * getValue(1, 0);
    }

    int det = 0;
    for (int j = 0; j < cols; j++) {
        int aij = getValue(0, j);
        det += aij * getAlgebraicCofactor(0, j);
    }
    return det;
}

Matrix Matrix::Adjoint() { return Cofactor().Transpose(); }

Matrix Matrix::Inverse() {
    int det = Determinant();
    if (det == 0) {
        throw runtime_error("Matrix is not invertible");
    }

    Matrix adj = Adjoint();
    Matrix result(rows, cols, adj.elements.size());

    for (auto &term : adj.elements) {
        result.addElement(term.row, term.col, term.value / det);
    }
    return result;
}

Matrix Matrix::Cofactor() {
    if (rows != cols) {
        throw invalid_argument("not square matrix");
    }

    Matrix result(rows, cols, rows * cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int cofactor = getAlgebraicCofactor(i, j);
            if (cofactor != 0) {
                result.addElement(i, j, cofactor);
            }
        }
    }
    return result;
}

/*額外增加之必要或幫助其他方法之方法*/
void Matrix::addElement(int row, int col, int value) {
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

int Matrix::getValue(int row, int col) const {
    for (const auto &term : elements) {
        if (term.row == row && term.col == col) {
            return term.value;
        }
    }
    return 0;
}

Matrix Matrix::getMinor(int excludeRow, int excludeCol) {
    Matrix minor(rows - 1, cols - 1, (rows - 1) * (cols - 1));
    for (const auto &term : elements) {
        if (term.row != excludeRow && term.col != excludeCol) {
            int newRow = term.row < excludeRow ? term.row : term.row - 1;
            int newCol = term.col < excludeCol ? term.col : term.col - 1;
            minor.addElement(newRow, newCol, term.value);
        }
    }
    return minor;
}

int Matrix::getAlgebraicCofactor(int i, int j) {
    Matrix minor = getMinor(i, j);
    int sign = ((i + j) % 2 == 0) ? 1 : -1;
    return sign * minor.Determinant();
}

void Matrix::Display() {
    vector<vector<int>> display(rows, vector<int>(cols, 0));

    for (const auto &term : elements) {
        display[term.row][term.col] = term.value;
    }

    int maxWidth = 1;
    for (const auto &row : display) {
        for (int val : row) {
            maxWidth = max(maxWidth, static_cast<int>(to_string(val).length()));
        }
    }

    for (const auto &row : display) {
        cout << "[";
        for (size_t j = 0; j < row.size(); ++j) {
            cout << setw(maxWidth) << row[j];
            if (j < row.size() - 1)
                cout << " ";
        }
        cout << "]\n";
    }
    cout << endl;
}

/*C++ main program to test each*/
int main() {
    try {
        // 測試 1：建立矩陣
        cout << "1. Create test matrices A B\n";
        Matrix A(3, 3, 5); // 3x3 矩陣，最多 5 個非零元素
        A.addElement(0, 0, 1);
        A.addElement(1, 1, 1);
        A.addElement(2, 2, 1);
        A.addElement(0, 2, 3);
        A.addElement(1, 2, 2);
        A.Display();

        Matrix B(3, 3, 5); // 3x3 矩陣，最多 5 個非零元素
        B.addElement(0, 0, 1);
        B.addElement(1, 1, 1);
        B.addElement(2, 2, 1);
        B.addElement(0, 1, 2);
        B.addElement(1, 2, 1);
        B.Display();

        // 測試 2：矩陣轉置
        cout << "\n2. Test matrix transpose A\n";
        Matrix AT = A.Transpose();
        AT.Display();

        // 測試 3：矩陣相加
        cout << "\n3. Test matrix add A+B\n";
        Matrix C = A.Add(B);
        C.Display();

        // 測試 4：矩陣相乘
        cout << "\n4. Test matrix multiply AxB\n";
        Matrix D = A.Multiply(B);
        D.Display();

        // 測試 5：計算行列式
        cout << "\n5. Test calculate determinant A\n";
        int det = A.Determinant();
        cout << "Determinant of A = " << det << endl;

        // 測試 6：計算 Adjoint
        cout << "\n6. Test Adjoint A\n";
        Matrix adj = A.Adjoint();
        adj.Display();

        // 測試 7：計算 Cofactor
        cout << "\n7. Test calculate Cofactor A\n";
        Matrix cof = A.Cofactor();
        cof.Display();

        // 測試 8：計算逆矩陣
        cout << "\n8. Test calculate Inverse A\n";
        Matrix inv = A.Inverse();
        inv.Display();

    } catch (const exception &e) {
        cout << "error occur: " << e.what() << endl;
    }

    return 0;
}
