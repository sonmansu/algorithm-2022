#include <iostream>
#include "../smtool.h"
using namespace std;

vector<vector<int>> table;

void printTable() {
    int len = table.size();
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            cout << table[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "==============================\n";
}

int main() {
//    string s;
//    cin >> s;
    string s = "mybagazcm";

    int len = s.length(); // 4
    cout<<"len:" << len<<endl;
    table.resize(len, vector<int>(len, 1));

    printTable();

    int same;
    int i = 0, j = 1;
    while (true) {
        if (s[i] == s[j]) same = 2;
        else same = 0;

        int maxVal = max(table[i+1][j-1] + same, table[i][j-1]);
        maxVal = max(maxVal, table[i+1][j]);
        table[i][j] = maxVal;

        i = i+1;
        j = j+1;

        if (j == len-1) {
            j = j - i + 1;
            i = 0;
        }
        if (j == len) break;
        printTable();
    }

    printTable();
    return 0;
}
