#include "../smtool.h"
#include <iostream>
#include <set>
using namespace std;

typedef pair<int, int> pii;

vector<vector<int>> tasks;
vector<vector<int>> sched;
vector<int> possibleIdxVec;

void printTasks() {
    for (auto w: tasks) {
        printf("%d, %d\n", w[0], w[1]);
    }
}
void printSched() {
    for (auto w: sched) {
        for (int i = 0; i < w.size(); i++) {
            printf("%d, ", w[i]);
        }
        cout << endl;
    }
}
bool cmp(const vector<int> &vii1, const vector<int> &vii2) {
    return (vii1[0] > vii2[0]) ;
}


int main() {
    int N, T, k;
    cin >> N >> T >> k; // work count, work days, machine counts
    tasks.resize(N, vector<int>(2));
    sched.resize(T+1, vector<int>(k, 0)); // index 0 is going to be empty

    for (int i = 0; i < N; i++) {
        cin >> tasks[i][0] >> tasks[i][1]; // cost, due day
    }
    sort(tasks.begin(), tasks.end(), cmp);
    LINE;
    printTasks();
    LINE;
    int maxCost = 0;
    vector<int> gaps;

    for (int i = 0; i < N; i++) {
        vector<int> task = tasks[i];
        int due = task[1];
        int cost = task[0];
        while (due > 0) {
            for (int j = 0; j < k; j++) { // machine count
                if (sched[due][j] == 0) {
                    sched[due][j] = cost; // save cost
                    gaps.push_back(cost);
                    maxCost += cost;
                    due = -1;
                    break;
                }
            }
            due--;
        }
        if (due == 0) { // didn't use
            possibleIdxVec.push_back(i);
        }
    }
    contout(possibleIdxVec);
    printSched();

    cout << maxCost << ' ';

    // find secondMax
    for (int i = 0; i < possibleIdxVec.size(); i++) {
        int possibleIdx = possibleIdxVec[i]; //9
        vector<int> task = tasks[possibleIdx];
        int due = task[1];
        int cost = task[0];

        while (due > 0) {
            for (int j = 0; j < k; j++) {
                if (cost-sched[due][j] == 0) continue;
                gaps.push_back(sched[due][j] - cost);
            }
            due--;
        }

    }
    contMout("\ngap: ", gaps);
    int minGap = *(min_element(gaps.begin(), gaps.end()));
    varMout ("minGap", minGap);
    cout << maxCost - minGap;




    return 0;
}