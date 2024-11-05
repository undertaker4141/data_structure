/*題目*/
/*Write a C++ function that multiplies two polynomials represented as in this
section. What is the computing time of your function?*/

#include <bits/stdc++.h>
using namespace std;
class Polynomial;
class Term {
    friend Polynomial;

  private:
    float coef; // coefficient
    int exp;    // exponent
};

class Polynomial {
  public:
    Polynomial() : termArray(nullptr), terms(0) {}
    ~Polynomial() { delete[] termArray; }
    void NewTerm(const float theCoeff, const int theExp);
    Polynomial Multiply(Polynomial b); // New multiplication function

  private:
    Term *termArray;
    int terms;
};

void Polynomial::NewTerm(const float theCoeff, const int theExp) {
    Term *temp = new Term[terms + 1];
    if (termArray) {
        copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    termArray[terms].coef = theCoeff;
    termArray[terms++].exp = theExp;
}

Polynomial Polynomial::Multiply(Polynomial b) {//題目要求增加之方法
    Polynomial c;
    for (int i = 0; i < terms; i++) {//兩個for迴圈分別遍歷第一個多項式和第二個多項式的每一項，計算這些項之間的乘積。
        for (int j = 0; j < b.terms; j++) {
            float newCoef = termArray[i].coef * b.termArray[j].coef;
            int newExp = termArray[i].exp + b.termArray[j].exp;
 
            bool find = false;// 標記是否找到相同的指數。
            for (int k = 0; k < c.terms; k++) {
                if (c.termArray[k].exp == newExp) {
                    // 如果在c中找到了一個指數為newExp的項，則直接將計算出的newCoef加到這個項的係數上。避免重複添加相同指數的項，並設定find為true。
                    c.termArray[k].coef += newCoef;
                    find = true;
                    break;
                }
            }
            // 如果在結果多項式中沒有找到相同指數的項（即find為false），且newCoef不為零，則將新的項加入到結果多項式c中。
            if (!find && newCoef != 0) {
                c.NewTerm(newCoef, newExp);
            }
        }
    }
    return c;
}

int main() { return 0; }
