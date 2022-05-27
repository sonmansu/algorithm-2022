#include <bits/stdc++.h>
using namespace std;
#define MAX_GASUNGBI  100000 // (each nutrients max:)25000 * 4

class Node {
  public:
    vector<int> puts;
    vector<int> nutSum; 
    int cost; 
    int gsb; 
    Node(const Node &n) {
        this->puts = n.puts;
        this->nutSum = n.nutSum;
        this->gsb = n.gsb;
        this->cost = n.cost;
    }
    Node(vector<int> puts, vector<int> nutSum, int cost, int gsb) {
        this->puts = puts;
        this->nutSum = nutSum;
        this->cost = cost;
        this->gsb = gsb;
    }
    bool operator<(const Node node) const {
        return (this->cost > node.cost);
    }
};

vector<int> criteria(4);
vector<vector<int>> diets; 
priority_queue<Node> pq;
vector<Node> solNodes;
set<vector<int>> finishedSet;

bool cmp(const vector<int> &v1, const vector<int> &v2) {
    if (v1[7] == v2[7]) {
        return v1[5] < v2[5]; 
    } else
        return v1[7] > v2[7]; 
}

int main() {
    int k;
    cin >> k;
    int minCost = 500 * k; 
    for (int i = 0; i < 4; i++) {
        cin >> criteria[i];
    }
    for (int i = 0; i < k; i++) {
        vector<int> row(8); 
        row[0] = i+1; 
        for (int j = 1; j < 6; j++) {
            cin >> row[j];
        }
        diets.push_back(row);
    }
    for (int i = 0; i < k; i++) {
        int sum = 0;
        for (int j = 1; j < 5; j++) {
            sum += diets[i][j];
        }
        diets[i][6] = sum; //sum of nutrients
        if (diets[i][5] != 0)
            diets[i][7] = sum / diets[i][5]; // GASUNGBI (sum / cost)
        else
            diets[i][7] = MAX_GASUNGBI;
    }

    sort(diets.begin(), diets.end(), cmp);
    for (auto diet: diets) { 
        vector<int> puts(k + 1); 
        puts[diet[0]] = 1; 
        vector<int> nutSum(4);
        for (int i = 1; i < 5; i++) {
            nutSum[i-1] = diet[i];
        }
        Node node(puts, nutSum, diet[5], diet[7]);
        pq.push(node);
    }
    while(!pq.empty()) {
        Node prom = pq.top();
        pq.pop();

        for (int i = 0; i < k; i++) { 
            vector<int> diet = diets[i];
            int ingNum = diet[0]; 
            int solFlag = 0;

            if (prom.puts[ingNum] == 0) {
                prom.puts[ingNum] = 1; 
                auto pos = finishedSet.find(prom.puts);
                if (pos == finishedSet.end()) {
                    finishedSet.insert(prom.puts);
                } else {
                    prom.puts[ingNum] = 0; //복구
                    continue;
                }


                for (int j = 0; j < 4; j++) {
                    prom.nutSum[j] += diet[j+1]; 
                    if (prom.nutSum[j] >= criteria[j]) {
                        solFlag++;
                    }
                }
                prom.cost += diet[5];
                prom.gsb += diet[7];
                if (solFlag == 4) {
                    if (prom.cost < minCost) {
                        minCost = prom.cost;
                        solNodes.clear(); 
                        solNodes.push_back(prom);
                    } else if (prom.cost == minCost) {
                        solNodes.push_back(prom);
                    }
                } else {
                    pq.push(prom);
                }

                break;
            }
        }
    }

    if (solNodes.size() == 1) {
        for (int i = 1; i < k+1; i++) {
            if (solNodes[0].puts[i] == 1) cout << i << ' ';
        }
    } else if (solNodes.size() == 0) {
        cout << "0";
    } else if (solNodes.size() > 1) {
        int maxAllNutSum = 0;
        int idx;
        vector<vector<int>> puts;
        vector<string> strPuts;
        for (int i = 0; i < solNodes.size(); i++) {
            auto node = solNodes[i];
            int allNutSum = 0;
            for (auto nutSum: node.nutSum) {
                allNutSum += nutSum;
            }
            if (allNutSum > maxAllNutSum) {
                strPuts.clear();
                maxAllNutSum = allNutSum;
                idx = i;
            } else if (allNutSum == maxAllNutSum) {
                string s;
                for (int j = 0; j < solNodes[i].puts.size(); j++) {
                    s += to_string(solNodes[i].puts[j]);
                }
                strPuts.push_back(s);
            }
        }
        if (strPuts.size() > 0) { 
            auto it = min_element(strPuts.begin(), strPuts.end());
            for (int i = 1; i < k+1; i++) {
                if ((*it)[i] == '1') cout << i << ' ';
            }

        } else { 
            for (int i = 1; i < k+1; i++) {
                if (solNodes[idx].puts[i] == 1) cout << i << ' ';
            }
        }
    }





    return 0;
}