#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<string>> tableStr;

bool cmp(const string &s1, const string &s2) {
    if (s1.length() > s2.length()) return true;
    else if (s1.length() == s2.length()) {
        return (s1 < s2);
    } else {
        return false;
    }
}

int main() {
    string s;
    cin >> s;

    int len = s.length(); // 4
    tableStr.resize(len, vector<string>(len, ""));
    // setting base condition
    for (int i = 0; i < len; i++) {
        tableStr[i][i] = s[i];
    }

    int i = 0, j = 1;
    string midStr, leftStr, downStr;
    while (true) {
        midStr = tableStr[i+1][j-1];
        leftStr = tableStr[i][j-1];
        downStr = tableStr[i+1][j];

        if (s[i] == s[j]) {
            midStr = s[i] + midStr + s[i];
        };

        string findStr; 

        vector<string> strV = {midStr, leftStr, downStr};
        sort(strV.begin(), strV.end(), cmp);
        findStr = strV[0];

        tableStr[i][j] = findStr;

        i = i+1;
        j = j+1;

        if (j == len) {
            j = j - i + 1;
            if (j == len) break;
            i = 0;
        }
    }
    cout << tableStr[0][len-1];

    return 0;
}
