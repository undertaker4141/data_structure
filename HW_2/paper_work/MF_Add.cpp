/*題目*/
/*Modify function Add so that it reduces the size of c.termArray to c.terms
prior to termination. With this modification, can we dispense with the data
member capacity?*/

#include <bits/stdc++.h>
using namespace std;
class Polynomial; // 參考課本程式
class Term {
    friend Polynomial;

  private:
    float coef; // coefficient
    int exp;    // exponent
};

class Polynomial {
  public:
    Polynomial()
        : termArray(nullptr), terms(0) {} // Construct the polynomial p(x) = 0.
    ~Polynomial() { delete[] termArray; }
    Polynomial
    Add(Polynomial poly); // Return the sum of the polynomials *this and poly.
    void NewTerm(const float theCoeff, const int theExp);

  private:
    Term *termArray; // array of nonzero terms
    int capacity;    // size of termArray, we can delete it
    int terms;       // number of nonzero terms
};

void Polynomial::NewTerm(const float theCoeff, const int theExp)
// Add a new term to the end of termArray
{
    if (terms == capacity) {
        capacity += 1;//初步修改，一次擴一格大小，發現其實capacity變數可以不用使用
        Term *temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete[] termArray; // deallocate old memory
        termArray = temp;
    }

    termArray[terms].coef = theCoeff;
    termArray[terms++].exp = theExp;
}

Polynomial Polynomial::Add(Polynomial b) // 參考課本程式碼
{ // Return the sum of the polynomials *this and b.
    Polynomial c;
    int aPos = 0, bPos = 0;
    while ((aPos < terms) && (bPos < b.terms)) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t)
                c.NewTerm(t, termArray[aPos].exp);
            aPos++;
            bPos++;
        } else if (termArray[aPos].exp < b.termArray[bPos].exp) {
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        } else {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }

    // add in remaining terms of *this
    for (; aPos < terms; aPos++) {
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    }
    // add in remaining terms of b(x)
    for (; bPos < b.terms; bPos++) {
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    }
    return c;
}

int main() { return 0; }