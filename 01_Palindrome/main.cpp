#include <iostream>
#include "../smtool.h"
using namespace std;

int N, wrong, similar;
string word;

int checkPalin(int startIdx, int endIdx) {
    while (startIdx < endIdx) {
        if (word[startIdx] == word[endIdx]) {
            startIdx++;
            endIdx--;
            continue;
        }

        wrong++;
        if (wrong >= 2) break;
        // ���ÿ� �Ǵ� ��쿣... �� �� �ϳ��� �����ϸ� ..
        if (word[startIdx+1] == word[endIdx] && word[startIdx] == word[endIdx-1]) {
            if (startIdx == endIdx-1) {
                startIdx++;
                continue;
            }
            cout << "�б� !" << endl;
            checkPalin(startIdx+1, endIdx); //��� 1 �� �غ�
            checkPalin(startIdx, endIdx-1);   //��� 2�� �غ�
        } else if (word[startIdx+1] == word[endIdx]) { // ���1�� ��
            startIdx++;
        } else if (word[startIdx] == word[endIdx-1]) { // ���2�� ��
            endIdx--;
        } else {
            wrong = -1;
            break;
        }

    }
    if (wrong == 0) return 1;
    else if (wrong == 1) {
        similar++;
        return 2;
    }
    else return 3;
}



int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> word; // ���⼭ �ڲ� �����
        varMout("word:", word);
        similar = 0;
        wrong = 0;
        int result = checkPalin(0, word.length()-1);

        if (result == 1) cout << "1\n";
        else if (similar > 0) cout << "2\n";
        else if (result == 3) cout << "3\n";
        else cout << "2\n";

    }
}
