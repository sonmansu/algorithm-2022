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
        if (fishVal != i) { //���� ���� ����
            if (fishVal > 0) {
                blockEven++;
                block.push_back(2);
            } else {
                blockOdd++;
                block.push_back(1);
            }
            index.push_back(i); //���� �ε��� ����
            for (j = i+1; (fish[j] == fish[j-1]+1); j++) {
//                cout << fish[j] << endl;
//                cout << fish[j-1] + 1 << endl;
            }
            index.push_back(j-1); //�� �ε��� ����

            i = j-1; //������ ���� ���� ����
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
            if (block[0] == 1 && block[1] == 2 && block[2] == 1) { //���� 1 2 1 ���Դµ�..
//                int idx1Start = index[0]; //����1�� ���� �ε��� ����
//                int idx1Val= abs(fish[idx1Start]);
//
//                int idx3End = index[5]; //����3�� �� �ε��� ����
//                int idx3Val = abs(fish[idx3End]);
//
//                if (idx1Start == idx3Val && idx1Val == idx3End) return "two\n";

                // ���� �߰� 1
                int idx1Start = index[0];
                int idx1StartVal = abs(fish[idx1Start]);

                int idx1End = index[1];
                int idx1EndVal = abs(fish[idx1End]);
                if (idx1Start == idx1EndVal) return "over\n";

                // ���� �߰� 2
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
                //���� �߰� 4
                int idx1Start = index[0];
                int idx1StartVal = abs(fish[idx1Start]);
                int  idx1End = index[1];
                int  idx1EndVal = abs(fish[idx1End]);
                if (idx1Start == idx1EndVal) return "over\n";


                idx1Start = index[2]; //�߰� ������ �����ε���
                int idx2End = index[5]; //������ ������ �� �ε���

                if ( abs(fish[idx1Start]) == idx2End ) return "two\n";
                else return "over\n";
            }

            else if (block[0] == 2 && block[1] == 1 && block[2] == 1) {
                //���� �߰� 3
                int idx1Start = index[4];
                int idx1StartVal = abs(fish[idx1Start]);
                int  idx1End = index[5];
                int  idx1EndVal = abs(fish[idx1End]);
                if (idx1Start == idx1EndVal) return "over\n";

                int idx2Start = index[0]; //ù ������ �����ε���
                 idx1End = index[3]; //�߰� ������ �� �ε���

                if ( abs(fish[idx1End]) == idx2Start ) return "two\n";
                else return "over\n";
            }
            else  return  "two\n";

        }
    } else { //blockEven�� 2 �̻���
        return  "over\n";
    }


}

int main() {
//    int k; //��Ʋ ũ��
    cin >> k;
    fish.reserve(k+1); //k�� �뷮�� Ȯ���س���
//    vector<int> fish(k);,
    for (int i = 0; i < 10; i++) { //5�� ����

        fish[0] = 0;
        for (int i = 1; i <= k; i++) { //�迭 �Է� ����
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
