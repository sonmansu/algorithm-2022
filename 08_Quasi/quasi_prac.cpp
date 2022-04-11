#include "../smtool.h"
#include <iostream>
#include <set>
using namespace std;

typedef pair<int, int> pii;
vector<vector<int>> table;
map<char, vector<int>> m;
map<pii, vector<pii>> locationM;
vector<vector<string>> stringTable;

struct Compare {
	bool operator() (const string &a, const string &b) const{
		if (a.size() == b.size())
			return a < b;
		else
			return a.size() > b.size();
	}
};
set<string, Compare> mySet;

void printTable() {
    int len = table.size();
    int x = 1000;
    int index = 0;

    cout << "00" << " | ";
    for (int j = 0; j < table[0].size(); j++) {
        if (j < 10)
            cout << '0';
        cout << j << ' ';
    }
    cout << "\n-----------------------\n";

    for (int i = 0; i < len; i++) {
        if (i < 10)
            cout << '0';
        cout << i << " | ";

        for (int j = 0; j < table[0].size(); j++) {
            if (table[i][j] < 10)
                cout << '0';
            cout << table[i][j] << ' ';
            x++;
        }
        cout << endl;
    }
    cout << "==============================\n";
}
void printM() {
    for (auto it = m.begin(); it != m.end(); ++it) {
        printf("'%c' : ", (*it).first );
        for (auto w : (*it).second) {
            cout << w << ", ";
        }
        cout << endl;
    }
    cout << endl;
}
void printLocationM() {
    for (auto it = locationM.begin(); it != locationM.end(); ++it) {
        printf("(%d, %d) : ", (*it).first.first, (*it).first.second);
        for (auto w : (*it).second) {
            printf("(%d, %d), ", w.first, w.second);
        }
        cout << endl;
    }
    cout << endl;
}
int main() {
    // string s1 = "goodbanana_box";  // size: n
    // string s2 = "cob_aonwanxabin"; // size: m
    string s1, s2;
    cin >> s1 >> s2;
    int s1Size = s1.size();
    int s2Size = s2.size();

    // table.resize(s1.size(), vector<int>(s2.size(), 0)); // size: n x m
    table.resize(s1.size()+2, vector<int>(s2.size()+2, 0)); // size: (n+2) x (m+2) // to avoid an out of range index error
    stringTable.resize(s1.size()+2, vector<string>(s2.size()+2, "")); // size: (n+2) x (m+2) // to avoid an out of range index error
    // step1. make map and table
    for (int i = 0; i < s1Size; i++) {
        vector<int> tempVec;
        char tempC = s1[i];
        if (m.find(tempC) != m.end()) { // if there is a key,
            for (auto w: m[tempC]) {
                table[i][w] = 1;
            }
        } else { // new key
            for (int j = 0; j < s2Size; j++) {
                if (tempC == s2[j]) {
                    table[i][j] = 1;
                    m[tempC].push_back(j); //  'g': {0}
                }
            }
        }
    }
    printTable();
    printM();
    // step2. read map and make locationMap
    for (int i = 0; i < s1Size; i++) {
        char tempC = s1[i]; //'a'
        auto tempVec = m[tempC]; // {4,8,11};
        for (int vecIdx = 0; vecIdx < tempVec.size(); vecIdx++) {
            int j = tempVec[vecIdx];
            if (table[i+1][j+1] == 1){
                locationM[{i, j}].push_back({i+1, j+1});
            } else if (table[i+2][j+2] == 1) {
                locationM[{i, j}].push_back({i+2, j+2});
            }
            if (table[i+1][j+2] == 1) {
                locationM[{i, j}].push_back({i+1, j+2});
            } 
            if (table[i+2][j+1] == 1) {
                locationM[{i, j}].push_back({i+2, j+1});
            } 
        }
    }
    printLocationM();
    // step 3. connect locationMap
    vector<string> substringVec;
    for (auto it = locationM.begin(); it != locationM.end(); it++) {
        pii key = (*it).first; // (0, 1)
        vector<pii> valueVec = (*it).second; // (1, 3), (2, 4) ....

        if (stringTable[key.first][key.second] == "") { // if it's empty
            stringTable[key.first][key.second] = s1[key.first]; // 'a'
        }
        for (int j = 0; j < valueVec.size(); j++) {
            pii tempKey = valueVec[j]; // (1,3)
            string tempStr = string(stringTable[key.first][key.second]) + s1[tempKey.first] ;
            varMout("tempStr: ", tempStr);
            if (locationM.find(tempKey) != locationM.end()) { // find tempKey
                stringTable[tempKey.first][tempKey.second] = tempStr;
            } else {
                mySet.insert(tempStr);
            }
        }
    }
    contMout("mySet: ", mySet);
    cout << *mySet.begin();

    return 0;
}