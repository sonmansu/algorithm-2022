#include <bits/stdc++.h>
using namespace std;

class Node {
  public:
    vector<int> puts, nutSum;
    int cost; 
    Node(vector<int> puts, vector<int> nutSum, int cost) {
        this->puts = puts; this->nutSum = nutSum; this->cost = cost;
    }
    bool operator<(const Node node) const {
        return (this->cost > node.cost);
    }
};

vector<int> criteria(4);vector<vector<int>> diets; 
priority_queue<Node> pq;vector<Node> solNodes;
set<vector<int>> mySet;

bool cmp(const vector<int> &v1, const vector<int> &v2) {
    if (v1[7] == v2[7]) return v1[5] < v2[5]; 
    else return v1[7] > v2[7]; 
}
int main() {
    int k;
    cin >> k;
    int minCost = 500 * k; 
    for (int i = 0; i < 4; i++)  cin >> criteria[i];
    for (int i = 0; i < k; i++) {
        vector<int> row(8); 
        row[0] = i+1; 
        for (int j = 1; j < 6; j++) cin >> row[j];
        diets.push_back(row);
    }
    for (int i = 0; i < k; i++) {
        int sum = 0;
        for (int j = 1; j < 5; j++)  sum += diets[i][j];
        diets[i][6] = sum; 
        diets[i][7] = diets[i][5] != 0 ? sum / diets[i][5] : 100000;
    }
    sort(diets.begin(), diets.end(), cmp);
    for (auto d: diets) { 
        vector<int> puts(k + 1), nutSum(4); 
        puts[d[0]] = 1; 
        for (int i = 1; i < 5; i++) nutSum[i-1] = d[i];
        Node node(puts, nutSum, d[5]);
        pq.push(node);
    }
    while(!pq.empty()) {
        Node prom = pq.top();
        pq.pop();
        for (int i = 0; i < k; i++) { 
            vector<int> diet = diets[i];
            int ingNum = diet[0], solFlag = 0; 

            if (prom.puts[ingNum] == 0) {
                prom.puts[ingNum] = 1; 
                auto pos = mySet.find(prom.puts);
                if (pos == mySet.end()) {
                    mySet.insert(prom.puts);
                } else {
                    prom.puts[ingNum] = 0; 
                    continue;
                }
                for (int j = 0; j < 4; j++) {
                    prom.nutSum[j] += diet[j+1]; 
                    if (prom.nutSum[j] >= criteria[j]) solFlag++;
                }
                prom.cost += diet[5];
                if (solFlag == 4) {
                    if (prom.cost < minCost) {
                        minCost = prom.cost;
                        solNodes.clear(); 
                        solNodes.push_back(prom);
                    } else if (prom.cost == minCost) {
                        solNodes.push_back(prom);
                    }
                    prom.puts[ingNum] = 0;
                } 
                pq.push(prom);
                break;
            }
        }
    }
    int solCnt = solNodes.size();
    if (solCnt == 1) {
        for (int i = 1; i < k+1; i++) {
            if (solNodes[0].puts[i] == 1) cout << i << ' ';
        }
    } else if (solCnt == 0) {
        cout << "0";
    } else {
        int maxAllNutSum = 0, idx;
        vector<string> strPuts;
        for (int i = 0; i < solCnt; i++) {
            auto node = solNodes[i];
            int allNutSum = 0;
            for (auto sum: node.nutSum) allNutSum += sum;
            if (allNutSum > maxAllNutSum) {
                strPuts.clear();
                maxAllNutSum = allNutSum;
                idx = i;
            } else if (allNutSum == maxAllNutSum) {
                string s;
                for (int j = 0; j < node.puts.size(); j++) {
                    s += to_string(node.puts[j]);
                }
                strPuts.push_back(s);
            }
        }
        if (strPuts.size() > 0) { 
            auto it = min_element(strPuts.begin(), strPuts.end());
            for (int i = 1; i < k+1; i++)
                if ((*it)[i] == '1') cout << i << ' ';
        } else { 
            for (int i = 1; i < k+1; i++)
                if (solNodes[idx].puts[i] == 1) cout << i << ' ';
        }
    }
    return 0;
}
