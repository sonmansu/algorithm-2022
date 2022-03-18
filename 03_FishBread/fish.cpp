#include <iostream>
#include <vector>

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
        if (fishVal != i) {
            if (fishVal > 0) {
                blockEven++;
                block.push_back(2);
            } else {
                blockOdd++;
                block.push_back(1);
            }
            index.push_back(i);
            for (j = i+1; (fish[j] == fish[j-1]+1); j++) {

            }
            index.push_back(j-1);
            i = j-1;
        }
    }
    if (blockEven == 0) {
        if (blockOdd == 1) return "one";
        else if (blockOdd == 2 || blockOdd == 0) return  "two";
        else return  "over";
    } else if (blockEven == 1) {
        if (blockOdd >= 3) return "over";
        else {
            if (block[0] == 1 && block[1] == 2 && block[2] == 1) {
                int idx1Start = index[0];
                int idx1StartVal = abs(fish[idx1Start]);

                int idx1End = index[1];
                if (idx1Start == abs(fish[idx1End])) return "over";

               idx1Start = index[4];
                 idx1StartVal = abs(fish[idx1Start]);
                 idx1End = index[5];
                if (idx1Start == abs(fish[idx1End])) return "over";
                int idx = index[0];
                int valIdx = abs(fish[idx]);
                if (idx == abs(fish[valIdx])) return "two";

                return "over";
            }

            else if (block[0] == 1 && block[1] == 1 && block[2] == 2) {
                int idx1Start = index[0];
                int idx1StartVal = abs(fish[idx1Start]);
                int  idx1End = index[1];
                if (idx1Start == abs(fish[idx1End])) return "over";
                idx1Start = index[2];
                int idx2End = index[5];
                if ( abs(fish[idx1Start]) == idx2End ) return "two";
                else return "over";
            }
            else if (block[0] == 2 && block[1] == 1 && block[2] == 1) {
                int idx1Start = index[4];
                int idx1StartVal = abs(fish[idx1Start]);
                int  idx1End = index[5];
                if (idx1Start == abs(fish[idx1End])) return "over";
                int idx2Start = index[0];
                 idx1End = index[3];

                if ( abs(fish[idx1End]) == idx2Start ) return "two";
                else return "over";
            }
            else  return  "two";
        }
    } else {
        return  "over";
    }
}

int main() {
    cin >> k;
    fish.reserve(k+1);
    for (int i = 0; i < 5; i++) {

        fish[0] = 0;
        for (int i = 1; i <= k; i++) {
            cin >> fish[i];
        }
        cout << operation() << '\n';

    }
}
