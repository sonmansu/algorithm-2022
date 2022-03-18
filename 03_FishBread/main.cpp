#include <iostream>
#include "../smtool.h"

using namespace std;
int k;
vector<int> fish;

int blockEven, blockOdd;

string operation() {
    vector<int> block, index;

    blockEven = 0;
    blockOdd = 0;
    int i, j;
    for (i = 1; i <= k; i++) {
        int fishVal = fish[i];
        if (fishVal != i) { //구간 분할 시작
            if (fishVal > 0) {
                blockEven++;
                block.push_back(2);
            } else {
                blockOdd++;
                block.push_back(1);
            }
            index.push_back(i); //시작 인덱스 저장
            for (j = i+1; (fish[j] == fish[j-1]+1); j++) {
//                cout << fish[j] << endl;
//                cout << fish[j-1] + 1 << endl;
            }
            index.push_back(j-1); //끝 인덱스 저장

            i = j-1; //새구간 시작 지점 설정
        }
    }
    cout << "blockOdd: " << blockOdd << ", blockEven: " << blockEven << endl;
    contMout("block vector: ", block);
    if (blockEven == 0) {
        if (blockOdd == 1) return "one\n";
        else if (blockOdd == 2 || blockOdd == 0) return  "two\n";
        else return  "over\n";
    } else if (blockEven == 1) {
        if (blockOdd >= 3) return "over\n";
        else {
            if (block[0] == 1 && block[1] == 2 && block[2] == 1) { //만약 1 2 1 나왔는데..
//                int idx1Start = index[0]; //구간1의 시작 인덱스 저장
//                int idx1Val= abs(fish[idx1Start]);
//
//                int idx3End = index[5]; //구간3의 끝 인덱스 저장
//                int idx3Val = abs(fish[idx3End]);
//
//                if (idx1Start == idx3Val && idx1Val == idx3End) return "two\n";

                // 새로 추가 1
                int idx1Start = index[0];
                int idx1StartVal = abs(fish[idx1Start]);

                int idx1End = index[1];
                int idx1EndVal = abs(fish[idx1End]);
                if (idx1Start == idx1EndVal) return "over\n";

                // 새로 추가 2
                 idx1Start = index[4];
                 idx1StartVal = abs(fish[idx1Start]);

                 idx1End = index[5];
                 idx1EndVal = abs(fish[idx1End]);
                if (idx1Start == idx1EndVal) return "over\n";

                // fish 86
                int idx = index[0];
                int valIdx = abs(fish[idx]);
                int val = abs(fish[valIdx]);
                if (idx == val) return "two\n";
                // fish 86



                return "over\n";



            }

            else if (block[0] == 1 && block[1] == 1 && block[2] == 2) {
                //새로 추가 4
                int idx1Start = index[0];
                int idx1StartVal = abs(fish[idx1Start]);
                int  idx1End = index[1];
                int  idx1EndVal = abs(fish[idx1End]);
                if (idx1Start == idx1EndVal) return "over\n";


                idx1Start = index[2]; //중간 구간의 시작인덱스
                int idx2End = index[5]; //마지막 구간의 끝 인덱스

                if ( abs(fish[idx1Start]) == idx2End ) return "two\n";
                else return "over\n";
            }

            else if (block[0] == 2 && block[1] == 1 && block[2] == 1) {
                //새로 추가 3
                int idx1Start = index[4];
                int idx1StartVal = abs(fish[idx1Start]);
                int  idx1End = index[5];
                int  idx1EndVal = abs(fish[idx1End]);
                if (idx1Start == idx1EndVal) return "over\n";

                int idx2Start = index[0]; //첫 구간의 시작인덱스
                 idx1End = index[3]; //중간 구간의 끝 인덱스

                if ( abs(fish[idx1End]) == idx2Start ) return "two\n";
                else return "over\n";
            }
            else  return  "two\n";

        }
    } else { //blockEven이 2 이상임
        return  "over\n";
    }


}

int main() {
//    int k; //빵틀 크기
    cin >> k;
    fish.reserve(k+1); //k의 용량을 확보해놓음
//    vector<int> fish(k);,
    for (int i = 0; i < 10; i++) { //5번 수행

        fish[0] = 0;
        for (int i = 1; i <= k; i++) { //배열 입력 받음
            cin >> fish[i];
        }
//        fish = {0, -3, -2, 6, 1, -5, -4};

        contMout("fish: ", fish);
        cout << operation();

        ENDL;

        LINE;
        LINE;

    }
}
