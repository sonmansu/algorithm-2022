#include <iostream>
#include <vector>
#include "timebomb.h"

using namespace std;

int main() {
    int N, result;
    vector<vector<int>> tournament;
    vector<int> index;

    box_ready();
    N = box_size();

    for (int i = 0; i < N; i++) {
        index.push_back(i+1);
    }

    tournament.push_back(index);

    int i = 0;
    while(true) {
        int length = tournament[i].size(); // 10
        vector<int> temp;

        if (length == 1) break;

        for (int j = 0; j < length; j=j+2) {
            if ( length-1 < j+1) {
                temp.push_back(tournament[i][j]);
                continue;
            }
            result = box_comp(tournament[i][j], tournament[i][j+1]);

            if (result == 1) {
                temp.push_back(tournament[i][j]);
            } else if (result == -1) {
                temp.push_back(tournament[i][j+1]);
            } else if (result == 0) {
                temp.push_back(tournament[i][j]);
            }
        }
        tournament.push_back(temp);
        i++;

    }
    // making second vector
    vector<int> second;
    int maxIdxVal = tournament[tournament.size()-1][0];
    int maxIdx = 0;
    for (int j = tournament.size()-2; j >= 0; j--) {

        if (tournament[j][maxIdx*2] == maxIdxVal) {
            if ( (maxIdx*2+1) <= tournament[j].size()-1 )
                second.push_back(tournament[j][maxIdx*2+1]);
            maxIdx *= 2;
        } else {
            second.push_back(tournament[j][maxIdx*2]);
            maxIdx = maxIdx*2+1;
        }
    }

    if (second.size() == 1) box_report(second[0]);

    result = box_comp(second[0], second[1]);
    int bigger;
    if (result == 1) {
        bigger = second[0];
    } else
        bigger = second[1];

    if (second.size() == 2) box_report(bigger);

    for (int j = 2; j < second.size(); j++) {
        result = box_comp(bigger, second[j]);

        if (result == 1) {
        } else if (result == -1) {
            bigger = second[j];
        }
    }
    box_report(bigger);

}
