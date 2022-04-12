#include <bits/stdc++.h>
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
} cmp;
set<string, Compare> mySet;

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int s1Size = s1.size(), s2Size = s2.size();

    table.resize(s1.size()+2, vector<int>(s2.size()+2, 0));
    stringTable.resize(s1.size()+2, vector<string>(s2.size()+2, "")); 
    for (int i = 0; i < s1Size; i++) {
        vector<int> tempVec;
        char tempC = s1[i];
        if (m.find(tempC) != m.end()) { 
            for (auto w: m[tempC]) {
                table[i][w] = 1;
            }
        } else { 
            for (int j = 0; j < s2Size; j++) {
                if (tempC == s2[j]) {
                    table[i][j] = 1;
                    m[tempC].push_back(j);
                }
            }
        }
    }
    for (int i = 0; i < s1Size; i++) {
        char tempC = s1[i]; 
        auto tempVec = m[tempC]; 
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
    if (locationM.size() == 0) {
        cout << (*m.begin()).first;
        return 0;
    }
    vector<string> substringVec;
    string tempStr, currStr;
    for (auto it = locationM.begin(); it != locationM.end(); it++) {
        pii key = (*it).first; 
        vector<pii> valueVec = (*it).second; 

        if (stringTable[key.first][key.second] == "") { 
            stringTable[key.first][key.second] = s1[key.first]; 
        }
        for (int j = 0; j < valueVec.size(); j++) {
            pii tempKey = valueVec[j]; // (1,3)
            tempStr = string(stringTable[key.first][key.second]) + s1[tempKey.first] ;
            if (locationM.find(tempKey) != locationM.end()) { 
                currStr = stringTable[tempKey.first][tempKey.second];
                if (currStr != "") { 
                    tempStr = min(currStr, tempStr, cmp);
                }
                stringTable[tempKey.first][tempKey.second] = tempStr;
            } else {
                mySet.insert(tempStr);
            }
        }
    }
    cout << *mySet.begin();

    return 0;
}