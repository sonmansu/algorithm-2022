#include "../smtool.h"
#include <iostream>
#include <set>
using namespace std;

stack<char> st;

bool visited[27] = {false, };
//int visited[27] = {0, };

vector<int> criteria(4);
vector<vector<int>> diets;
priority_queue<int> pq;

int main() {
    int k;
    cin >> k;
    for (int i = 0; i < 4; i++) {
        cin >> criteria[i];
    }
    for (int i = 0; i < k; i++) {
        vector<int> row(7); // 5 + sum of nutrients  + GASUNGBI
        for (int j = 0; j < 5; j++) {
            cin >> row[j];
        }
        diets.push_back(row);
    }
    // make sum of nutrients  + GASUNGBI
    for (int i = 0; i < k; i++) {
        int sum = 0;
        for (int j = 0; j < 4; j++) {
            sum += diets[i][j];
        }
        diets[i][5] = sum; //sum of nutrients
        diets[i][6] = sum / diets[i][3]; // GASUNGBI
    }

    LINE;
    contMout("criteria", criteria);
    LINE;
    for (int i = 0; i < k; i++) {
        contout(diets[i]);
    }
    LINE;

    

    return 0;
}