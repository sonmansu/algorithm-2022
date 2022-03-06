#include <iostream>
using namespace std;


int main() {
    int N, wrong, startIdx, endIdx;
    string word;

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> word;
        startIdx = 0;
        endIdx = word.length() - 1;
        wrong = 0;
        while (startIdx < endIdx) {
            if (word[startIdx] == word[endIdx]) {
                startIdx++;
                endIdx--;
                continue;
            } else if (word[startIdx+1] == word[endIdx]) {
                startIdx++;
            } else if (word[startIdx] == word[endIdx-1]) {
                endIdx--;
            } else {
                wrong = -1;
                break;
            }
            wrong++;
            if (wrong >= 2) break;
        }
        if (wrong == 0) cout << "1\n";
        else if (wrong == 1) cout << "2\n";
        else cout << "3\n";
    }

}
