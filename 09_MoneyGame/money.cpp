#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

vector<char> op(30); // operator's max : 29
vector<int> num(31); // max int count: 30
vector<vector<pii>> table;

vector<int> minmaxVec;
int operation(pii p1, pii p2, char op) {
    int res;
    int big, small, small1, small2, small3;
    switch (op) {
    case '+':
        minmaxVec.push_back(p1.first + p2.first);
        minmaxVec.push_back(p1.second + p2.second);
        minmaxVec.push_back(p1.first + p2.second);
        minmaxVec.push_back(p1.second + p2.first);
        break;
    case '-':
        minmaxVec.push_back(p1.first - p2.first);
        minmaxVec.push_back(p1.second - p2.second);
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
int main() {
    table.resize(31, vector<pii>(31, make_pair(0, 0)));
    int tempNum;
    char tempOp;
    cin >> num[1];

    int n;
    char c;
    while (scanf(" %c %d", &c, &n) == 2) {
        op[idx] = c;
        idx++;
        num[idx] = n;
    }
    // base condition [1][1]
    for (int i = 1; i <= idx; i++) {
        table[i][i] = {num[i], num[i]};
    }
    // base condition.2 [1][2] ~ [4][5]
    for (int i = 1; i <= idx - 1; i++) {
        int res =  operation(num[i], num[i+1], op[i]);
        table[i][i + 1] = {res, res};
    }
    // start dp operation
    for (int gap = 2; gap < idx; gap++) { 
        int i, j;
        for (i = 1, j = i + gap; j <= idx; i++, j++) { 
            minmaxVec.clear();
            for (int opIdx = i; opIdx < j; opIdx++) {
                char tempOp = op[opIdx];
                operation(table[i][opIdx], table[opIdx+1][j], op[opIdx]); // fill  minmax vector
            }
            auto result = minmax_element(minmaxVec.begin(), minmaxVec.end());
            table[i][j] = {*result.second, *result.first}; // save max, min
        }
    }
    cout << table[1][idx].first;

    return 0;
}
