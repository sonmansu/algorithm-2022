#include <iostream>
using namespace std;

int N, wrong = 0, similar = 0;
string word;

int checkPalin(int startIdx, int endIdx) {
    while (startIdx < endIdx) {
        if (word[startIdx] == word[endIdx]) {
            startIdx++;
            endIdx--;
            continue;
        }

        // 동시에 되는 경우엔... 둘 중 하나라도 만족하면 ..
        if (word[startIdx+1] == word[endIdx] && word[startIdx] == word[endIdx-1]) {
            checkPalin(startIdx+1, endIdx); //경우 1 로 해봄
            checkPalin(startIdx, endIdx-1);   //경우 2로 해봄
        } else if (word[startIdx+1] == word[endIdx]) { // 경우1만 됨
            startIdx++;
        } else if (word[startIdx] == word[endIdx-1]) { // 경우2만 됨
            endIdx--;
        } else {
            wrong = -1;
            break;
        }
        wrong++;
        if (wrong >= 2) break;
    }
    if (wrong == 0) return 1;
    else if (wrong == 1) {
        return 2;
        similar++;
    }
    else return 3;
}



int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> word;
        similar = 0;
        int result = checkPalin(0, word.length()-1);
        if (result == 1) cout << "1\n";
        else if (similar > 0) cout << "2\n";
        else if (result == 3) cout << "3\n";
    }
}
