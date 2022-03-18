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

            i = j-1;
        }
    }

    if (blockEven == 0) {
        if (blockOdd == 1) return "one\n";
        else if (blockOdd == 2 || blockOdd == 0) return  "two\n";
        else return  "over\n";
    } else if (blockEven == 1) {
        if (blockOdd >= 3) return "over\n";
        else {
            if (block[0] == 1 && block[1] == 2 && block[2] == 1) {
                int idx = index[0];
                int valIdx = abs(fish[idx]);
                int val = abs(fish[valIdx]);

                if (idx == val) return "two\n";
                else return "over\n";

            } else  return  "two\n";
        }
    } else {
        return  "over\n";
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

        cout << operation();


    }
}
