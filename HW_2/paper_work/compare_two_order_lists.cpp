/*題目*/
/*If a = (a_0, ..., a_{n-1}) and b = (b_0, ..., b_{m-1}) are ordered lists,
 then a < b if:
     a_i = b_i for 0 <= i < j and a_j < b_j,
     or, if a_i = b_i for 0 <= i < n and n < m.
Write a function that returns -1, 0, or +1, depending upon whether a < b, a = b,
or a > b. Assume that the a_is and b_js are integer.*/

#include <bits/stdc++.h>
using namespace std;

int compare_lists(const int *a, const int *b, int a_size, int b_size) {

    int min_len = min(a_size, b_size);

    for (size_t i = 0; i < min_len; i++) {
        if (*(a + i) < *(b + i)) {
            return -1;
        } else if (*(a + i) > *(b + i)) {
            return 1;
        }
    }

    // all elements up to min_len are equal
    // compare length
    if (a_size < b_size) {
        return -1;
    } else if (a_size > b_size) {
        return 1;
    } else {
        return 0;
    }
}

void print_list(const int *a, const int a_size) {
    for (int i = 0; i < a_size; i++) {
        cout << *(a + i) << " ";
    }
    std::cout << "\n";
}

int main() {
    cout << " compare two ordered lists : returns -1, 0, or +1, depending upon whether a < b, a = b,or a > b." << endl;
    cout<< endl;
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, };
    int b[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    // -1
    std::cout << "a: ";
    print_list(a, 8);

    cout << "b: ";
    print_list(b, 9);
    cout << "compare result: " << compare_lists(a, b, 8, 9) << endl;

    // 1
    int c[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int d[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "c: ";
    print_list(c, 11);

    cout << "d: ";
    print_list(d, 10);
    cout << "compare result: " << compare_lists(c, d, 11, 10) << endl;

    // 0
    int e[11] = {0, 1, 2, 3, 4, 5};
    int f[11] = {0, 1, 2, 3, 4, 5};
    cout << "e: ";
    print_list(e, 6);

    cout << "f: ";
    print_list(f, 6);
    cout << "compare result: " << compare_lists(e, f, 6, 6) << endl;
    return 0;
}
