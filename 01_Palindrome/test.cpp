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
    fp와 fp1를 라인 단위로 비교를 합니다.
    fgets가 읽은 것이 NULL 인지 검사를 합니다.*/


    while( fgets( buffer, BUFLEN, fp ) ) {
        while( fgets( buffe, BUFLEN, fp1 ) ) {
            /*
            buffer와 buffe의 비교는 문자열 비교함수 strcmp()함수를 이용합니다. */

            if( strcmp( buffer, buffe ) != 0 ) {
                printf("다른 문자열 발견: %s", buffer );
                wrong++;
            }
            break;
            count = count + 1;
        }

        /*
        fp의 한 라인에 대하여 fp1 라인들의 문자열과 비교한후
        fp1의 화일 포인터를 처음 위치로 돌립니다.
        fp  : n  라인
        fp1 : n1 라인이라면 총 n x n1번 비교가 이루어 집니다 */

    }

    printf( "비교 횟수 %d\n", count );
    if (wrong == 0) cout << "맞습니다!!\n";

    /* 파일 닫기 */
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
        cout << "파일을 찾을 수 없습니다!" << endl;
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
            } else if (word[startIdx+1] == word[endIdx]) { //유사회문 가능성 존재
                startIdx++;
            } else if (word[startIdx] == word[endIdx-1]) { //유사회문 가능성 존재
                endIdx--;
            } else { // 회문 아님, 출력 후바로 종료
//                cout << "3\n";
                wrong = -1;
                break;
            }
            wrong++;
            if (wrong >= 2) break;
        }
        if (wrong == 0) fout << "1\n";
        else if (wrong == 1) fout << "2\n";
        else fout << "3\n"; //wrong이 -1이거나 2이상..

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

        cout << finStr + "파일 수행 시작\n";
        operation();

        fileDiff(foutStr.c_str(), answerStr.c_str());

        fin.close();
        fout.close();

    }


}
