#include <iostream>
#include "../smtool.h"
using namespace std;

vector<vector<int>> table;
vector<vector<string>> tableStr;

// void printTable() {
//     int len = table.size();
//     int x = 1000;
//     int index = 0;

//     cout << "00" << " | ";
//     for (int j = 0; j < len; j++) {
//         if (j < 10) cout << '0'; 
//         cout << j << ' ';
//     }
//     cout << "\n-----------------------\n";

//     for (int i = 0; i < len; i++) {
//         if (i < 10) cout << '0';
//         cout << i << " | ";
    
//         for (int j = 0; j < len; j++) {
//             if (table[i][j] < 10) cout << '0'; 
//             cout << table[i][j] << ' ';
//             x++;
//         }
//         cout << endl;
//     }
//     cout << "==============================\n";
// }

void printTableStr() {
    int len = tableStr.size();
    int x = 1000;
    int index = 0;

    cout << "00" << " | ";
    for (int j = 0; j < len; j++) {
        if (j < 10) cout << '0'; 
        cout << j << ' ';
    }
    cout << "\n-----------------------\n";

    for (int i = 0; i < len; i++) {
        if (i < 10) cout << '0';
        cout << i << " | ";
    
        for (int j = 0; j < len; j++) {
            cout << tableStr[i][j] << ' ';
            x++;
        }
        cout << endl;
    }
    cout << "==============================\n";
}

bool cmp(const string &s1, const string &s2) {
    if (s1.length() > s2.length()) return true;
    else if (s1.length() == s2.length()) {
        return (s1 < s2);
    } else {
        return false;
    }
}

int main() {
//    string s;
//    cin >> s;
    // string s = "sometime_summer_time"; //ei_mm_ie
    string s = "system_computer_language_intelligence"; //ecelngagnlece
    // string s = "abcdefghijkflmn"; //fgf
    // string s = "abcdefghijklmn"; //a
    // string s = "cdab";
    // string s = "abccea";
    cout << s << endl;

    int len = s.length(); // 4
    cout<<"len:" << len <<endl;
    tableStr.resize(len, vector<string>(len, ""));
    // setting base condition
    for (int i = 0; i < len; i++) {
        tableStr[i][i] = s[i];
    }

    int i = 0, j = 1;
    while (true) {
        string midStr = tableStr[i+1][j-1];
        string leftStr = tableStr[i][j-1];
        string downStr = tableStr[i+1][j];

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
        // if (j == len+1) break;
    }
    printTableStr();
    cout << tableStr[0][len-1];

    return 0;
}
