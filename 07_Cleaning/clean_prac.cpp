#include <iostream>
#include "../smtool.h"
#include <map>
using namespace std;

#define YEAR_3 1096

vector<vector<int>> clean;
typedef pair<int, int> pii;
multimap<int, pii> mm;

void printmm() {
    for ( auto it = mm.begin(); it != mm.end(); ++it) {
        std:: cout << "  [" << (*it).first << "/ " << (*it).second.first << ", " << (*it).second.second << "]" << endl;
    }
    cout << endl;
}

int main() {
    int N;
    cin >> N;

    clean.resize(1096, vector<int>(2)); //0 ~ 1095

    // Save input
    int startDay, endDay, money;
    for (int i = 0; i < N; i++) {
        cin >> startDay >> endDay >> money;
        mm.insert({endDay, make_pair(startDay, money)}); // multi.insert( {"a",3 } );
    }
    printmm();
    // base condition
    clean[0][0] = 0; //day
    clean[0][1] = 0; //money

    int lastDay = (*--mm.end()).first;
    
    // for (int i = 1; i < YEAR_3; i++) {
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

    
}