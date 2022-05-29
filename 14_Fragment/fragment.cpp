#include <bits/stdc++.h>
using namespace std;

vector<string> input;
int finish = 0;

/* find kth element */
vector<int> findElement(int &k, const map<char, vector<int>> &bucketM) {
    int cnts = 0;
    vector<int> indexVec;
    int vectorSize;

    for (auto it = bucketM.begin(); it != bucketM.end(); it++) {
        vectorSize = (*it).second.size();
        cnts +=  vectorSize;

        if ( k <= cnts ) {
            if (k == cnts && vectorSize == 1) {
                cout << (*it).second[0] << '\n';
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
map<char, vector<int>> makeBucket(vector<int> indexVec, int radix) {
    map<char, vector<int>> bucketM;

    for (int i = 0; i < indexVec.size(); i++) {
        int strIdx = indexVec[i];
        string s = input[strIdx];
        char c = s[radix];
        bucketM[c].push_back(strIdx);
    }
    return bucketM;
}

int main() {
    int startK;

    map<char, vector<int>> firstBucketM;

    string tempS;
    input.push_back("NaN"); // dummy value. to make sure the string value start from index 1

    /* 01. get input */
    cin >> startK;
    while (cin >> tempS) {
        input.push_back(tempS);
    }

    int radix = 0;

    /* 02. make first bucket */
    for (int i = 1; i < input.size(); i++) {
        string s = input[i];
        char startChar = s[radix];
        firstBucketM[startChar].push_back(i);
    }


    for (int i = 0; i < 3; i++) { // repeat 3 times
        map<char, vector<int>> bucketM = firstBucketM;
        radix = 0;
        int k = startK - 1 + i;
        finish = 0;

        while(true) {
            vector<int> indexVec = findElement(k, bucketM);
            if (finish) break;
            radix++;
            bucketM = makeBucket(indexVec, radix);
        }
    }

    return 0;
}
