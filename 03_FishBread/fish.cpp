#include <iostream>
#include <vector>

using namespace std;
int k;
vector<int> fish;

int blockEven, blockOdd;

void operation() {
    blockEven = 0;
    blockOdd = 0;
    int i, j;
    for (i = 1; i <= k; i++) {
        int fishVal = fish[i];
        if (fishVal != i) {
            if (fishVal > 0) {
                blockEven++;
            } else {
                blockOdd++;
            }
            for (j = i+1; (fish[j] == fish[j-1]+1); j++) {
            }

            i = j-1;
        }
    }
}

int main() {
    cin >> k;
    fish.reserve(k+1);
    for (int i = 0; i < 5; i++) {

        for (int i = 1; i <= k; i++) {
            cin >> fish[i];
        }

        operation();

        if (blockEven == 0) {
            if (blockOdd == 1) cout << "one\n";
            else if (blockOdd == 2 || blockOdd == 0) cout << "two\n";
            else cout << "over\n";
        } else if (blockEven == 1) {
            if (blockOdd >= 3) cout <<"over\n";
            else cout << "two\n";
        } else {
            cout << "over\n";
        }

    }
}
