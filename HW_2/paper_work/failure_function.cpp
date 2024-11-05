/*Compute the failure function for each of the following patterns:
 (a) a a a b
 (b) a b a b a a
 (c) a b a a b a a b b*/

#include <bits/stdc++.h>
using namespace std;

vector<int> build_failure_function(string &t) {
    vector<int> F(t.size());//函數接收一個字串 t，計算該字串的失敗函數並以 vector<int> 形式返回。
    F[0] = -1;//第一個位置設定為 -1，表示沒有匹配的前綴

/*使用變數 pos，表示當前字串中有效的「匹配前綴-後綴」的長度，初始值為 -1。
從 i = 1 開始逐一檢查 t[i]，以構建整個字串的失敗函數。
若當前字符 t[i] 與 t[pos + 1] 不匹配，則將 pos 更新為 F[pos]，直到找到一個匹配位置或 pos = -1。
如果 t[i] 與 t[pos + 1] 匹配，則 pos++ 表示匹配前綴-後綴長度增加。
最後將當前 pos 設為 F[i]，並返回結果。*/
    for (int i = 1, pos = -1; i < t.size(); i++) {
        while (~pos && t[i] != t[pos + 1])
            pos = F[pos];

        if (t[i] == t[pos + 1])
            pos++;

        F[i] = pos;
    }
    return F;
}

int main() {
    cout << "failure function of a: " << endl;
    string str_a = "aaaab";
    vector<int> a = build_failure_function(str_a);
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;

    cout << "failure function of b: " << endl;
    string str_b = "ababaa";
    vector<int> b = build_failure_function(str_b);
    for (auto i : b) {
        cout << i << " ";
    }
    cout << endl;

    cout << "failure function of c: " << endl;
    string str_c = "abaabaabb";
    vector<int> c = build_failure_function(str_c);
    for (auto i : c) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
