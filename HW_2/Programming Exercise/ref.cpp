#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <string>

class Matrix // 三元組，<列，行，值>，的集合，其中列與行為非負整數，並且它的組合是唯一的；值也是個整數。
{
private:
    struct Triple
    {
        int row, col, value;
        Triple(int r, int c, int v) : row(r), col(c), value(v) {}

        bool operator<(const Triple &other) const
        {
            if (row != other.row)
                return row < other.row;
            return col < other.col;
        }
    };

    int rows, cols, capacity;
    std::vector<Triple> terms;

    Matrix getMinor(int excludeRow, int excludeCol);

    int getValue(int row, int col);

    int getAlgebraicCofactor(int i, int j);

public:
    // 建構子函式，建立一個有 r 列 c 行並且具有放 t 個非零項的容量
    Matrix(int r, int c, int t);
    // 新增元素
    void AddTerm(int row, int col, int value);

    // 回傳將 *this 中每個三元組的行與列交換後的轉置矩陣
    Matrix Transpose();

    // 如果 *this 和 b 的維度一樣，那麼就把相對應的項相加，
    // 亦即，具有相同列和行的值會被迴傳；否則 throw exception.
    Matrix Add(Matrix b);

    // 如果 *this 中的 column 和 b 的 row 一樣，回傳的矩陣就是 *this 和 b 相乘的結果。
    // 否則 throw exception.
    Matrix Multiply(Matrix b);

    // 如果 *this 是一個 square matrix，回傳 det(*this).
    int Determinant();
    // 如果 *this 是一個 square matrix，回傳 adj(*this).
    Matrix Adjoint();
    // 如果 *this 是一個 square matrix，回傳 *this 的反矩陣。
    Matrix Inverse();
    // 如果 *this 是一個 square matrix，回傳 *this 的 cofactor
    Matrix Cofactor();

    void Display();
};

Matrix::Matrix(int r, int c, int t) : rows(r), cols(c), capacity(t)
{
    if (r < 0 || c < 0 || t < 0)
        throw std::invalid_argument("dimensions and capacity must non-zero integer");
    rows = r;
    cols = c;
    capacity = t;
    terms.reserve(capacity);
}

Matrix Matrix::getMinor(int excludeRow, int excludeCol)
{
    Matrix minor(rows - 1, cols - 1, terms.size());
    for (Triple term : terms)
    {
        if (term.row == excludeRow || term.col == excludeCol)
            continue;
        int newRow = term.row > excludeRow ? term.row - 1 : term.row;
        int newCol = term.col > excludeCol ? term.col - 1 : term.col;
        minor.AddTerm(newRow, newCol, term.value);
    }
    return minor;
}

int Matrix::getValue(int row, int col)
{
    for (Triple term : terms)
    {
        if (term.row == row && term.col == col)
        {
            return term.value;
        }
    }
    return 0; // 如果找不到元素，返回0
}

int Matrix::getAlgebraicCofactor(int i, int j)
{
    Matrix minor = getMinor(i, j);
    int sign = ((i + j) % 2 == 0) ? 1 : -1;
    return sign * minor.Determinant();
}

void Matrix::AddTerm(int row, int col, int value)
{
    if (row >= rows || col >= cols)
        throw std::out_of_range("row or col position overflow");
    if (terms.size() >= capacity)
        throw std::overflow_error("capacity overflow");
    // 檢查是否已經存在相同位置的元素
    for (Triple term : terms)
    {
        if (term.row == row && term.col == col)
        {
            term.value = value;
            return;
        }
    }
    terms.push_back(Triple(row, col, value));
    std::sort(terms.begin(), terms.end());
}

Matrix Matrix::Transpose()
{
    Matrix result(cols, rows, capacity);
    for (Triple term : terms)
    {
        result.AddTerm(term.col, term.row, term.value);
    }
    return result;
}

Matrix Matrix::Add(Matrix b)
{
    if (rows != b.rows || cols != b.cols)
    {
        throw std::invalid_argument("dimensions is not fit");
    }

    Matrix result(rows, cols, capacity + b.terms.size());
    size_t i = 0, j = 0;

    while (i < terms.size() && j < b.terms.size())
    {
        if (terms[i].row < b.terms[j].row ||
            (terms[i].row == b.terms[j].row && terms[i].col < b.terms[j].col))
        {
            result.AddTerm(terms[i].row, terms[i].col, terms[i].value);
            i++;
        }
        else if (terms[i].row > b.terms[j].row ||
                 (terms[i].row == b.terms[j].row && terms[i].col > b.terms[j].col))
        {
            result.AddTerm(b.terms[j].row, b.terms[j].col, b.terms[j].value);
            j++;
        }
        else
        {
            int sum = terms[i].value + b.terms[j].value;
            if (sum != 0)
            {
                result.AddTerm(terms[i].row, terms[i].col, sum);
            }
            i++;
            j++;
        }
    }

    while (i < terms.size())
    {
        result.AddTerm(terms[i].row, terms[i].col, terms[i].value);
        i++;
    }

    while (j < b.terms.size())
    {
        result.AddTerm(b.terms[j].row, b.terms[j].col, b.terms[j].value);
        j++;
    }

    return result;
}

Matrix Matrix::Multiply(Matrix b)
{
    if (cols != b.rows)
    {
        throw std::invalid_argument("dimensions not fit, cannot multiply");
    }

    Matrix result(rows, b.cols, rows * b.cols); // 最壞情況的容量估計
    Matrix bTranspose = b.Transpose();          // 轉置 B 以便更容易訪問 row

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < b.cols; j++)
        {
            int sum = 0;
            bool hasValue = false;

            // 計算 C[i,j] = Σ(A[i,k] * B[k,j])
            for (Triple termA : terms)
            {
                if (termA.row != i)
                    continue;
                for (Triple termB : bTranspose.terms)
                {
                    if (termB.row != j || termB.col != termA.col)
                        continue;
                    sum += termA.value * termB.value;
                    hasValue = true;
                }
            }

            if (hasValue && sum != 0)
            {
                result.AddTerm(i, j, sum);
            }
        }
    }

    return result;
}

int Matrix::Determinant()
{
    if (rows != cols)
    {
        throw std::invalid_argument("not square matrix");
    }

    if (rows == 1)
    {
        return getValue(0, 0);
    }

    if (rows == 2)
    {
        return getValue(0, 0) * getValue(1, 1) - getValue(0, 1) * getValue(1, 0);
    }

    // 使用第一行展開：det(A) = Σ(a[0][j] * A[0][j])
    int det = 0;
    for (int j = 0; j < cols; j++)
    {
        int aij = getValue(0, j);
        det += aij * getAlgebraicCofactor(0, j);
    }
    return det;
}

Matrix Matrix::Cofactor()
{
    if (rows != cols)
    {
        throw std::invalid_argument("not square matrix");
    }

    Matrix result(rows, cols, rows * cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Matrix minor = getMinor(i, j);
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            int cofactor = sign * minor.Determinant();
            if (cofactor != 0)
            {
                result.AddTerm(i, j, cofactor);
            }
        }
    }
    return result;
}

Matrix Matrix::Adjoint()
{
    if (rows != cols)
    {
        throw std::invalid_argument("not square matrix");
    }

    // 計算 cofactor 矩陣
    Matrix cofactorMatrix = Cofactor();

    // 伴隨矩陣為 cofactor 矩陣的轉置
    return cofactorMatrix.Transpose();
}

Matrix Matrix::Inverse()
{
    int det = Determinant();
    if (det == 0)
    {
        throw std::runtime_error("is not invertible");
    }

    Matrix cofactorMatrix = Cofactor();
    Matrix result(rows, cols, cofactorMatrix.terms.size());

    for (Triple term : cofactorMatrix.terms)
    {
        result.AddTerm(term.row, term.col, term.value / det);
    }

    return result.Transpose();
}

void Matrix::Display()
{
    // 用二維 vector 暫存 matrix
    std::vector<std::vector<int>> display(rows, std::vector<int>(cols, 0));

    for (Triple term : terms)
    {
        display[term.row][term.col] = term.value;
    }

    // 計算最大數字寬度以對齊輸出
    int maxWidth = 1;
    for (const auto &row : display)
    {
        for (int val : row)
        {
            int width = std::to_string(val).length();
            if (val < 0)
                width++; // 考慮負號
            maxWidth = std::max(maxWidth, width);
        }
    }

    // 打印矩陣
    for (const auto &row : display)
    {
        std::cout << "[";
        for (size_t j = 0; j < row.size(); ++j)
        {
            std::cout << std::setw(maxWidth) << row[j];
            if (j < row.size() - 1)
                std::cout << " ";
        }
        std::cout << "]\n";
    }
    std::cout << std::endl;
}

void printMatrix(const std::string &name, Matrix &mat)
{
    std::cout << "\nTest" << name << " " << "Result:\n";
    mat.Display();
    std::cout << "Test done.\n";
}

int main()
{
    try
    {
        std::cout << "Start testing...\n\n";

        // 測試 1：建立矩陣
        std::cout << "1. Create test matrices\n";
        Matrix A(4, 4, 7); // 4x4 矩陣，最多 7 個非零元素
        A.AddTerm(0, 0, 1);
        A.AddTerm(1, 1, 1);
        A.AddTerm(1, 2, 1);
        A.AddTerm(1, 3, 1);
        A.AddTerm(2, 1, 1);
        A.AddTerm(2, 2, -1);
        A.AddTerm(3, 3, -1);
        printMatrix("Matrix A", A);

        Matrix B(4, 4, 6);// 4x4 矩陣，最多 6 個非零元素
        B.AddTerm(0, 0, 1);
        B.AddTerm(0, 2, 2);
        B.AddTerm(1, 1, 1);
        B.AddTerm(1, 3, -2);
        B.AddTerm(2, 2, -1);
        B.AddTerm(3, 3, 1);
        printMatrix("Matrix B", B);

        // 測試 2：矩陣轉置
        std::cout << "\n2. Test matrix transpose\n";
        Matrix AT = A.Transpose();
        printMatrix("Transpose of A", AT);

        // 測試 3：矩陣相加
        std::cout << "\n3. Test matrix add\n";
        Matrix C = A.Add(B);
        printMatrix("A + B", C);

        // 測試 4：矩陣相乘
        std::cout << "\n4. Test matrix multiply\n";
        Matrix D = A.Multiply(B);
        printMatrix("A * B", D);

        // 測試 5：計算行列式
        std::cout << "\n5. Test calculate determinant\n";
        int det = A.Determinant();
        std::cout << "Determinant of A = " << det << std::endl;

        // 測試 6：計算 Adjoint
        std::cout << "\n6. Test Adjoint\n";
        Matrix adj = A.Adjoint();
        printMatrix("Adjoint A", adj);

        // 測試 7：計算 Cofactor
        std::cout << "\n7. Test calculate Cofactor\n";
        Matrix cof = A.Cofactor();
        printMatrix("Cofactor of A", cof);

        // 測試 8：計算逆矩陣
        std::cout << "\n8. Test calculate Inverse\n";
        Matrix inv = A.Inverse();
        printMatrix("Inverse A", inv);

        // 測試錯誤處理
        std::cout << "\n9. Test error handling\n";
        try
        {
            Matrix invalid(3, 3, 1);
            invalid.AddTerm(4, 4, 1); // 應該拋出異常
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "catch error successfully: " << e.what() << std::endl;
        }

        // 測試矩陣維度不匹配的情況
        std::cout << "\n10. Test dimensions not fit\n";
        try
        {
            Matrix E(2, 3, 3);
            Matrix F(4, 2, 3);
            E.Multiply(F); // 應該拋出異常
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "catch error successfully: " << e.what() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "error occur: " << e.what() << std::endl;
    }

    return 0;
}
