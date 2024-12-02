/*Write a C++ Function to evaluate a polynomial at the point x, where x is a real number. 
Assume that the polynomial is represented as a circularly linked list with a header node*/


#include<iostream>
using namespace std;

class Polynomial {
private:
    class Term {
    public:
        float coefficient;  // 係數
        int exponent;      // 指數
        Term* next;        // 指向下一個節點的指標
        
        Term(float coef = 0, int exp = 0) : coefficient(coef), exponent(exp), next(nullptr) {}
    };
    Term* header;  // 表頭節點

public:
    Polynomial();  
    void addTerm(float coef, int exp);  // 新增項式
    float evaluate(float x);  // 計算多項式在 x 點的值
};

Polynomial::Polynomial() {
    header = new Term();
    header->next = header;  // 循環鏈結(dummy head)
}

// 新增項式
void Polynomial::addTerm(float coef, int exp) {
    if (coef == 0) return;  // 係數為 0 不需要加入
    
    Term* newTerm = new Term(coef, exp);
    Term* current = header;
    
    // 插入到鏈結串列的尾部
    while (current->next != header) {
        current = current->next;
    }
    
    newTerm->next = header;
    current->next = newTerm;
}

// 計算多項式在 x 點的值
float Polynomial::evaluate(float x) {
    if (header->next == header) {
        return 0;  // 空多項式
    }
    
    float result = 0;
    Term* current = header->next;
    
    while (current != header) {
        float term = current->coefficient;
        for (int i = 0; i < current->exponent; i++) {
            term *= x;
        }
        result += term;
        current = current->next;
    }
    
    return result;
}

int main() {
    Polynomial poly;
    
    // 新增多項式項：3x² + 2x + 1
    poly.addTerm(3, 2);
    poly.addTerm(2, 1);
    poly.addTerm(1, 0);
    
    float x = 2;
    float result = poly.evaluate(x);
    cout << "Value at x = " << x << " is: " << result << endl;
    
    return 0;
}


