#include "../smtool.h"
#include <bits/stdc++.h>
using namespace std;

vector<string> input;
multimap<char, int> bucketM;

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

    /* 02. make first bucket */
    for (int i = 1; i < input.size(); i++) {
        string s = input[i];
        char startChar = s[0];
        bucketM.insert( {startChar, i} );
    }

    printmm(bucketM);

    /* 03. start repeating process - find kth element */
    int cnts = 0;
    for (auto it = bucketM.begin(); it != bucketM.end(); it++) {
        char key = (*it).first;
        cout << bucketM.count(key) << endl;
    }
    
    return 0;
}