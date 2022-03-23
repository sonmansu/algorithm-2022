#include <iostream>
#include "../smtool.h"
#include "timebomb.h"

using namespace std;

int main() {
    int N, result;
    vector<vector<int>> tournament;
    vector<int> index;

    box_ready();
    N = box_size();
    varout(N);

//    index.reserve(N+1);
    for (int i = 0; i < N; i++) {
        index.push_back(i+1);
//        index[i] = i+1; //idx 집어넣음
    }
    ENDL;

    tournament.push_back(index);

    // making tournament vector
    int i = 0;
    while(true) {
        contMout("tournament[i]:", tournament[i]);
        int length = tournament[i].size(); // 10
        vector<int> temp;

        if (length == 1) break;

        for (int j = 0; j < length; j=j+2) {
            if ( length-1 < j+1) {
                cout <<"인덱스초과\n";
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
    // print
    LINE;
    for (auto w: tournament) {
        for (auto ww: w) {
            cout << ww << " ";
        }
        cout << endl;
    }
    LINE;
    // making second vector
    vector<int> second;
    int maxIdxVal = tournament[tournament.size()-1][0];
    int maxIdx = 0;
    for (int j = tournament.size()-2; j >= 0; j--) {
        contMout("second vec: ", second);
        int left = tournament[j][maxIdx*2]; // temporary

        if (tournament[j][maxIdx*2] == maxIdxVal) {
            if ( (maxIdx*2+1) <= tournament[j].size()-1 )
                second.push_back(tournament[j][maxIdx*2+1]);
            maxIdx *= 2;
        } else {
            second.push_back(tournament[j][maxIdx*2]);
            maxIdx = maxIdx*2+1;
        }
    }
    contMout("second", second);

    //second중에서 최댓값 찾음..
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
