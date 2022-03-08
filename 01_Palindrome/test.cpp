#include <iostream>
#include "../smtool.h"
using namespace std;

#include <cstring>
#include <fstream>
#include <iostream>
ifstream fin;
ofstream fout;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFLEN 100


int test() {

}
int fileDiff(const char *  file1, const char * file2) {
    FILE *fp;
    FILE *fp1;

    char buffer[BUFLEN];
    char buffe[BUFLEN];

    int count = 0, wrong = 0;

    if((fp=fopen(file1,"r")) == NULL) {
        fprintf(stderr,"Error opening file.");
        exit(1);
    }

    if((fp1=fopen(file2,"r")) == NULL) {
        fprintf(stderr,"Error opening file.");
        exit(1);
    }

    /*
    fp�� fp1�� ���� ������ �񱳸� �մϴ�.
    fgets�� ���� ���� NULL ���� �˻縦 �մϴ�.*/


    while( fgets( buffer, BUFLEN, fp ) ) {
        while( fgets( buffe, BUFLEN, fp1 ) ) {
            /*
            buffer�� buffe�� �񱳴� ���ڿ� ���Լ� strcmp()�Լ��� �̿��մϴ�. */

            if( strcmp( buffer, buffe ) != 0 ) {
                printf("�ٸ� ���ڿ� �߰�: %s", buffer );
                wrong++;
            }
            break;
            count = count + 1;
        }

        /*
        fp�� �� ���ο� ���Ͽ� fp1 ���ε��� ���ڿ��� ������
        fp1�� ȭ�� �����͸� ó�� ��ġ�� �����ϴ�.
        fp  : n  ����
        fp1 : n1 �����̶�� �� n x n1�� �񱳰� �̷�� ���ϴ� */

    }

    printf( "�� Ƚ�� %d\n", count );
    if (wrong == 0) cout << "�½��ϴ�!!\n";

    /* ���� �ݱ� */
    fclose(fp);
    fclose(fp1);

    return 0;
}



int operation() {
    int N, wrong;
//    vector<char> word;
    string word;

//    cin >> N;
    if (fin.is_open()) {
        fin >> N;
    } else {
        cout << "������ ã�� �� �����ϴ�!" << endl;
    }

    for (int i = 0; i < N; i++) {
//        cin >> word;
        fin >> word;
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
        if (wrong == 0) fout << "1\n";
        else if (wrong == 1) fout << "2\n";
        else fout << "3\n"; //wrong�� -1�̰ų� 2�̻�..

    }

}

int main() {
    int fileCnt = 5;
    string baseStr = ".\\sample_data\\";
    string finStr, foutStr, answerStr;
    for(int i= 1; i <= fileCnt; i++) {
        finStr = baseStr;
        foutStr = baseStr;
        answerStr = baseStr;
        if (i < 10) {
            finStr += '0';
            foutStr += '0';
            answerStr += '0';
        }
        finStr += to_string(i) + ".inp";
        foutStr += to_string(i) + "My.out";
        answerStr += to_string(i) + ".out";

        fin.open(finStr);
        fout.open(foutStr);

        cout << finStr + "���� ���� ����\n";
        operation();

        fileDiff(foutStr.c_str(), answerStr.c_str());

        fin.close();
        fout.close();

    }


}
