/*A matrix is a rectangular array of numbers. When the number of rows and the 
number of columns of a matrix are the same, we called the matrix a square 
matrix. Implement the below Matrix ADT that is extended from ADT 2.4 in page 
97 in C++.*/

#include <bits/stdc++.h>
using namespace std;

class SparseMatrix;//參考課本程式
class MatrixTerm
{
    friend SparseMatrix;
    friend ostream &operator<<(ostream &os, const SparseMatrix &matrix);
    friend istream &operator>>(istream &is, SparseMatrix &matrix);

private:
    int row, col, value;
};

// A set of triples, <row, column, value>, where row and column are non-negative
//  integers and form a unique combination; value is also an integer.
class SparseMatrix
{
    friend ostream &operator<<(ostream &os, const SparseMatrix &matrix);
    friend istream &operator>>(istream &is, SparseMatrix &matrix);

public:
    // The constructor function creates a SparseMatrix with
    //  r rows, c columns, and a capacity of t nonzero terms.
    SparseMatrix(int r, int c, int t) : rows(r), cols(c), terms(0), capacity(t)
    {
        if (r < 0 || c < 0 || t < 0)
            throw invalid_argument("Negative dimensions or capacity");
        smArray = new MatrixTerm[capacity];
    }
    ~SparseMatrix()
    {
        delete[] smArray;
    }

private:
    int rows, cols, terms, capacity;
    MatrixTerm *smArray;
};

/*使用者輸入稀疏矩陣的非零項數量，並將每個非零項的行、列和值分別儲存到 MatrixTerm 陣列中。若輸入的非零項數量超出容量，則拋出錯誤。*/ 
istream &operator>>(istream &is, SparseMatrix &matrix)//重載之方法 >>
{
    cout << "Enter the number of non-zero terms: ";
    is >> matrix.terms;
    if (matrix.terms > matrix.capacity)
    {
        throw overflow_error("Number of terms exceeds matrix capacity");
    }

    cout << "Enter each term as row, column value (separate by space):" << endl;
    for (int i = 0; i < matrix.terms; i++)
    {
        is >> matrix.smArray[i].row >> matrix.smArray[i].col >> matrix.smArray[i].value;
    }
    return is;
}

/*以矩陣格式輸出稀疏矩陣。*/
ostream &operator<<(ostream &os, const SparseMatrix &matrix)//重載之方法 <<
{
    int current_term = 0;
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            if (current_term < matrix.terms &&
                matrix.smArray[current_term].row == i &&
                matrix.smArray[current_term].col == j)
            {
                os << setw(4) << matrix.smArray[current_term++].value;
            }
            else
            {
                os << setw(4) << 0;
            }
        }
        os << endl;
    }
    return os;
}
int main()
{
    return 0;
}
