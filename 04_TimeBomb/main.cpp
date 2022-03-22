#include <iostream>
#include "../smtool.h"
#include "timebomb.h"

using namespace std;

int main() {
    int N, result, answer;
    vector<vector<int>> tournament;
    vector<int> index;
    int parentI;

    box_ready();
    N = box_size();
    varout(N);

//    index.reserve(N+1);
    for (int i = 0; i < N; i++) {
        index.push_back(i+1);
//        index[i] = i+1; //idx 집어넣음
    }
    for (int i = 0; i < N; i++) {
        cout << index[i] << ' ';
    }
    ENDL;

    tournament.push_back(index);
//    cout << tournament.size(); ENDL;
//    cout << tournament[0].size(); ENDL;
//    for (int i = 0; i < N; i++) {
//        cout << tournament[0][i] << ' ';
//    }

    // print
    for (auto w: tournament) {
        for (auto ww: w) {
            cout << ww << " ";
        }
        cout << endl;
    }



//    for (int i = 1; i < N; i=i+2) {
//        result = box_comp(i, i+1);
//        if (result == 1) {
//            temp.push_back(i);
//        } else if (result == -1) {
//            temp.push_back(i+1);
//        } else if (result == 0) {
//            temp.push_back(i);
//        }
//    }
//    tournament.push_back(temp);

    int i = 0;
    while(true) {
        contMout("tournament[i]:", tournament[i]);
        int length = tournament[i].size(); // 10
        vector<int> temp;

        if (length == 1) break;

        for (int j = 0; j < length; j=j+2) {
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
    // save
    vector<int> second;
    int maxIdx = tournament[tournament.size()-1][0];
    int idx = 0;
    varout(tournament.size());
    for (int j = tournament.size()-2; j >= 0; j--) {
        contMout("second: ", second);
        int left = tournament[j][idx*2];

        if (tournament[j][idx*2] == maxIdx) {
            if ( (idx*2+1) > tournament[j].size()-1 ) {
                idx *= 2;
                continue;
            }
            second.push_back(tournament[j][idx*2+1]);
            idx = idx*2;
        } else {
            second.push_back(tournament[j][idx*2]);
            idx = idx*2+1;
        }
    }
    contMout("second", second);

    //second중에서 최댓값 찾음..

    for (int j = 0; j < second.size(); j=j+2) {
        result = box_comp(second[j], second[j+1]);

        if (result == 1) {
            answer = second[j];
        } else if (result == -1) {
            answer = second[j+1];
        }
    }
    box_report(answer);


}
