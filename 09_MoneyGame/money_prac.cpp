#include "../smtool.h"
#include <iostream>
#include <set>
using namespace std;

typedef pair<int, int> pii;

vector<char> op(30); // operator's max : 29
vector<int> num(31); // max int count: 30
vector<vector<pii>> table;

vector<int> minmaxVec;
int operation(pii p1, pii p2, char op) {
    int res;
    switch (op) {
    case '+': 
    // 1 big + big / 2. small + small
        minmaxVec.push_back(p1.first + p2.first); 
        minmaxVec.push_back(p1.second + p2.second); 
        break;
    case '-':
    //1. big - small / 2. small - big
        minmaxVec.push_back(p1.first - p2.second);
        minmaxVec.push_back(p1.second - p2.first);
        break;
    case '*':
        minmaxVec.push_back(p1.first * p2.first);
        minmaxVec.push_back(p1.second * p2.second);
        minmaxVec.push_back(p1.first * p2.second);
        minmaxVec.push_back(p1.second * p2.first);
        break;
    }
    return res;
}
int operation(int x, int y, char op) {
    int res;
    switch (op) {
    case '+': 
    // 1 big + big / 2. small + small
        res = x + y;
        break;
    case '-':
    //1. big - small / 2. small - big
        res = x - y;
        break;
    case '*':
        res = x * y;
        break;
    }
    return res;
}
int idx = 1;
void printTable() {
    for (int i = 1; i <= idx; i++) {
        for (int j = 1; j <= idx; j++) {
            printf("(%d, %d) ", table[i][j].first, table[i][j].second);
        }
        cout << endl;
    }
    cout << "===================================";
}

int main() {
    table.resize(31, vector<pii>(31, make_pair(0, 0)));
    int tempNum;
    char tempOp;

    cin >> num[1];
    cout << num[1] << '\n';

    int n;
    char c;
    while (scanf(" %c %d", &c, &n) ==
           2) { // while(scanf("%d %d",&a,&b) != EOF) 도 가능
        op[idx] = c;
        idx++;
        num[idx] = n;
        cout << c << ' ' << n << endl;
    }
    contMout("op vector:", op);
    contMout("num vector:", num);
    varout(idx);
    // base condition [1][1]
    for (int i = 1; i <= idx; i++) {
        table[i][i] = {num[i], num[i]};
    }
    // base condition.2 [1][2] ~ [4][5]
    for (int i = 1; i <= idx - 1; i++) {
        int res =  operation(num[i], num[i+1], op[i]);
        table[i][i + 1] = {res, res};
    }
    printTable();
    // start dp operation
    for (int gap = 3; gap < idx; gap++) { // before gap is 3, it is filled with base conditions
        int i, j;
        for (i = 1; j = i + gap; j <= idx) { // 배열 채워나가는 순서
            minmaxVec.clear(); 
            // table[i][j] 값 구하기
            for (int opIdx = i; opIdx < j; opIdx++) {
                char tempOp = op[opIdx];
                operation(table[i][opIdx], table[opIdx+1][j], op[opIdx]); // fill  minmax vector
            }
            auto result = minmax_element(minmaxVec.begin(), minmaxVec.end());
            table[i][j] = {*result.first, *result.second}; // save max, min
        }
    }
    LINE;
    printTable();

    return 0;
}
