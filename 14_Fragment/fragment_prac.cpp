#include "../smtool.h"
#include <bits/stdc++.h>
using namespace std;

vector<string> input;
map<char, vector<int>> bucketM;
int finish = 0;

/* find kth element */
vector<int> findElement(int &k) {
    int cnts = 0;
    vector<int> indexVec;
    int vectorSize;

    for (auto it = bucketM.begin(); it != bucketM.end(); it++) {
        vectorSize = (*it).second.size();
        cout <<  vectorSize << endl;
        cnts +=  vectorSize;

        if ( k <= cnts ) {
            if (k == cnts && vectorSize == 1) {
                cout << "답:" << indexVec[0] << ' '; 
                finish = 1; //finish
                return(indexVec); 
            }
            indexVec = (*it).second;
            k =  vectorSize - (cnts - k); // update
            return(indexVec);
        }
    }
}

/* 04. make new bucketM again in indexVector */
void makeBucket(vector<int> indexVec, int radix) {
    bucketM.clear();

    for (int i = 0; i < indexVec.size(); i++) {
        int strIdx = indexVec[i];
        string s = input[strIdx];
        char c = s[radix];
        bucketM[c].push_back(strIdx);
    }
}

int main() {
    int k;
    string tempS;
    input.push_back("NaN"); // dummy value. to make sure the string value start from index 1

    /* 01. get input */
    cin >> k;
    while (cin >> tempS) {
        input.push_back(tempS);
    }
    LINE;
    contout(input);

    int radix = 0;

    /* 02. make first bucket */
    for (int i = 1; i < input.size(); i++) {
        string s = input[i];
        char startChar = s[radix];
        bucketM[startChar].push_back(i);
    }
    printvm(bucketM);

    while(true) {
        vector<int> indexVec = findElement(k);
        if (finish) return 0;
        radix++;
        makeBucket(indexVec, radix);
    }
    
    return 0;
}