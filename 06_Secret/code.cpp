#include <iostream>
#include "../smtool.h"
using namespace std;

vector<vector<int>> table;
vector<vector<string>> tableStr;

void printTable() {
    int len = table.size();
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
            if (table[i][j] < 10) cout << '0'; 
            cout << table[i][j] << ' ';
            x++;
        }
        cout << endl;
    }
    cout << "==============================\n";
}

// bool cmp(const )
int main() {
//    string s;
//    cin >> s;
    // string s = "sometime_summer_time";
    // string s = "abcdefghijkflmn";
    // string s = "abcdefghijklmn";
    string s = "cdab";
    // string s = "abccea/";
    cout << s << endl;
    int len = s.length(); // 4
    cout<<"len:" << len<<endl;
    table.resize(len, vector<int>(len, 0));
    tableStr.resize(len, vector<string>(len, 0));
    // setting base condition
    for (int i = 0, j = 0; i < len; i++, j++) {
        table[i][j] = 1;
        tableStr[i][j] = s[i];
    }

    printTable();

    int same;
    int i = 0, j = 1;
    while (true) {
        if (s[i] == s[j]) same = 2;
        else same = 0;

        int mid = table[i+1][j-1] + same;
        int left = table[i][j-1];
        int down = table[i+1][j];

        string midStr = tableStr[i+1][j-1];
        string leftStr = tableStr[i][j-1];
        string downStr = tableStr[i+1][j];
        /* table 원소 비교 */
        // 1. 원소가 다 같으면 세개 중에 젤 빠른거 기록
        // 2. max가 두개이면 두개 중 젤 빠른 거 기록  (min 찾기)? 
        // 3. 하나만 제일 크면 그거 기록

        if (mid == left && mid == down) {
            dic(midStr, leftStr);
        }


        
        int maxVal = max(table[i+1][j-1] + same, table[i][j-1]);
        maxVal = max(maxVal, table[i+1][j]);



        table[i][j] = maxVal;

        i = i+1;
        j = j+1;

        if (j == len) {
            j = j - i + 1;
            i = 0;
        }
        if (j == len+1) break;
        // printTable();
    }

    printTable();
    return 0;
}
