#include <iostream>
#include "../smtool.h"

using namespace std;


int main() {
    int N, wrong;
//    vector<char> word;
    string word;

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> word;
        int leng = word.length();
        int startIdx = 0, endIdx = word.length() - 1;
        wrong = 0;
        while (startIdx < endIdx) {
            if (word[startIdx] == word[endIdx]) {
                startIdx++;
                endIdx--;
                continue;
            } else if (word[startIdx+1] == word[endIdx]) { //����ȸ�� ���ɼ� ����
                startIdx++;
            } else if (word[startIdx] == word[endIdx-1]) { //����ȸ�� ���ɼ� ����
                endIdx--;
            } else { // ȸ�� �ƴ�, ��� �Ĺٷ� ����
//                cout << "3\n";
                wrong = -1;
                break;
            }
            wrong++;
            if (wrong >= 2) break;
        }
        if (wrong == 0) cout << "1\n";
        else if (wrong == 1) cout << "2\n";
        else cout << "3\n"; //wrong�� -1�̰ų� 2�̻�..



    }

}
