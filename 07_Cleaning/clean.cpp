#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> requests;
vector<vector<int>> clean;

bool cmp(const vector<int> &w1, const vector<int> &w2) {
    if (w1[1] < w2[1]) return true;
    else false;
}
bool binaryCmp(const vector<int> &vec, int value) {
    return vec[1] < value; // compare with end day
}
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;
    requests.resize(N, vector<int>(3));
    clean.resize(N, vector<int>(2));

    // Save input
    for (int i = 0; i < N; i++) {
        cin >> requests[i][0] >> requests[i][1] >> requests[i][2];
    }
    sort(requests.begin(), requests.end(), cmp);

    // Set base condition
    clean[0][0] = requests[0][2]; //money
    clean[0][1] = requests[0][1] - requests[0][0] + 1; // working days

    // Make dp table
    for (int i = 1; i < N; i++) {
        // case 1. include ith work
        int startDay = requests[i][0];
        
        // find the day which finishs earlier than the startDay
        auto it = lower_bound(requests.begin(), requests.begin() + i, startDay, binaryCmp);
        int idx = it - requests.begin() -1;

        int money1 = requests[i][2];
        int day1 = requests[i][1]- requests[i][0] + 1; 
        if (idx != -1 && clean[idx][0] > 10) {
            money1 += clean[idx][0] - 10;
            day1 += clean[idx][1];
        }
        // case 2. exclude ith work
        int money2 = clean[i-1][0];
        int day2 = clean[i-1][1];

        // find max between case 1 and case 2
        if (money1 == money2) {
            if (day1 < day2) {
                clean[i][0] = money1;
                clean[i][1] = day1;
            } else {
                clean[i][0] = money2;
                clean[i][1] = day2;
            }
        } else if (money1 > money2) {
            clean[i][0] = money1;
            clean[i][1] = day1;
        } else {
            clean[i][0] = money2;
            clean[i][1] = day2;
        }
    }
    cout << clean[N-1][0] << ' ' << clean[N-1][1];

    return 0;
}