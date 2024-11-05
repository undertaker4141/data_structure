/*If x = (x_0, ..., x_{m-1}) and y = (y_0, ..., y_{n-1}) are strings,
where x_i and y_i are letters of the alphabet, then
x is less then y if x_i = y_i for 0 <= i < j and x_j < y_j
or if x_i = y_i for 0 <= i <= m and m < n.
Write an algorithm that takes two strings x, y and returns either -1, 0, or +1 if x < y, x = y, or x > y repectively.*/

#include <bits/stdc++.h>
using namespace std;

int compareStrings(string x, string y)
{
    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0; // exactly equal
}
int main()
{
    string str1 = "apple";
    string str2 = "banana";
    string str3 = "applab";
    string str4 = "apple";
    // Comparing str1 and str2
    int result1 = compareStrings(str1, str2);
    if (result1 == -1)
        cout << "str1 < str2" << endl;
    else if (result1 == 1)
        cout << "str1 > str2" << endl;
    else
        cout << "str1 == str2" << endl;

    // Comparing str1 and str3
    int result2 = compareStrings(str1, str3);
    if (result2 == -1)
        cout << "str1 < str3" << endl;
    else if (result2 == 1)
        cout << "str1 > str3" << endl;
    else
        cout << "str1 == str3" << endl;

    // Comparing str1 and str4
    int result3 = compareStrings(str1, str4);
    if (result3 == -1)
        cout << "str1 < str4" << endl;
    else if (result3 == 1)
        cout << "str1 > str4" << endl;
    else
        cout << "str1 == str4" << endl;

    return 0;
}