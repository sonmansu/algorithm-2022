#include <iostream>
#include "../smtool.h"

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
        if (fishVal != i) { //���� ���� ����
            if (fishVal > 0) {
                blockEven++;
            } else {
                blockOdd++;
            }
            for (j = i+1; (fish[j] == fish[j-1]+1); j++) {
//                cout << fish[j] << endl;
//                cout << fish[j-1] + 1 << endl;
            }

            i = j-1; //������ ���� ���� ����
        }
    }
}

int main() {
//    int k; //��Ʋ ũ��
    cin >> k;
    fish.reserve(k+1); //k�� �뷮�� Ȯ���س���
//    vector<int> fish(k);,
    for (int i = 0; i < 5; i++) { //5�� ����

        fish[0] = 0;
        for (int i = 1; i <= k; i++) { //�迭 �Է� ����
            cin >> fish[i];
        }
//        fish = {0, -3, -2, 6, 1, -5, -4};

        contMout("fish: ", fish);

        operation();
        cout << "blockOdd: " << blockOdd << ", blockEven: " << blockEven << endl;
        ENDL;

        if (blockEven == 0) {
            if (blockOdd == 1) cout << "one\n";
            else if (blockOdd == 2 || blockOdd == 0) cout << "two\n";
            else cout << "over\n";
        } else if (blockEven == 1) {
            if (blockOdd >= 3) cout <<"over\n";
            else cout << "two\n";
        } else { //blockEven�� 2 �̻���
            cout << "over\n";
        }

//        if (blockEven >= 2) cout << "over\n";
//        else if (blockEven ==1) cout << "two\n";
//        else if (blockEven ==0 && blockOdd ==2) cout << "two\n";
//        else cout << "one\n";
        LINE;
        LINE;

    }
}
