#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> clean;
typedef pair<int, int> pii;
multimap<int, pii> mm;

int main() {
    // ios_base :: sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    int N;
    cin >> N;
    // Save input
    int startDay, endDay, money;
    for (int i = 0; i < N; i++) {
        cin >> startDay >> endDay >> money;
        mm.insert({endDay, make_pair(startDay, money)}); 
    }
    int lastDay = (*--mm.end()).first;
    clean.resize(lastDay+1, vector<int>(2)); //0 ~ lastDay
    // base condition
    clean[0][0] = 0; //day
    clean[0][1] = 0; //money
    for (int i = 1; i <= lastDay; i++) {
        if (mm.find(i) != mm.end()) { // i exists
            auto pair_it = mm.equal_range(i);
            // case 2. exclude ith work
            int m2 = clean[i-1][1];
            int d2 = clean[i-1][0];

            // case 1. include ith work
            auto it = pair_it.first;

            int m1 = (*it).second.second;
            int d1 = i - (*it).second.first + 1;
            if (clean[(*it).second.first -1][1] > 0) {
                m1 += clean[(*it).second.first -1][1] - 10;
                d1 += clean[(*it).second.first -1][0];
            }
            // compare with ith works
            while (++it != pair_it.second) {
                int t_m1 = (*it).second.second;
                int t_d1 = i - (*it).second.first + 1;
                if (clean[(*it).second.first -1][1] > 0) {
                    t_m1 += clean[(*it).second.first -1][1] - 10;
                    t_d1 += clean[(*it).second.first -1][0];
                }
                // compare and renew
                if ((t_m1 > m1) || (t_m1 == m1 && t_d1 < d1)) {
                    // renew m1 and d1
                    m1 = t_m1;
                    d1 = t_d1;
                }
            }
            // compare case 1 and 2
            if (m1 > m2) {
                clean[i][1] = m1;
                clean[i][0] = d1;
            } else if (m1 < m2) {
                clean[i][1] = m2;
                clean[i][0] = d2;
            } else { //same
                if (d1 < d2) {
                    clean[i][1] = m1;
                    clean[i][0] = d1;
                } else {
                    clean[i][1] = m2;
                    clean[i][0] = d2;
                }
            }
        } else { // i doesn't exist
            clean[i] = clean[i-1];
        }
    }
  
    cout << clean[lastDay][1] << ' ' << clean[lastDay][0];
    return 0;
}