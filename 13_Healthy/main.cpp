#include "../smtool.h"
#include <iostream>
#include <set>
#include <bits/stdc++.h>
using namespace std;
#define MAX_GASUNGBI  100000 // (each nutrients max:)25000 * 4

class Node {
  public:
    vector<int> puts; // 재료 갯수만큼
    vector<int> nutSum; // 영양분 합
    int cost; //가격
    int gsb; // 가성비
    // 생성자
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
    // 그냥 점수에 상관 없이 학번기준 학번이 작은것이 Top 을 유지 한다
    bool operator<(const Node node) const {
        //노드들 끼리 비교할떈 가격 낮은걸 반환 하는게 나을듯
        return (this->cost > node.cost);
//        if (this->gsb == node.gsb) {
//            return (this->cost > node.cost); // 가격 낮은대로
//        } else
//            return (this->gsb < node.gsb); // 가성비 큰 순서대로
    }
};
void printNode(const Node &n) {
    varout("==========노드출력시작=============");
//    contMout("n.puts:", n.puts);
    cout << "n.puts: ";
    for (int i = 0; i < (n.puts).size(); i++) {
        if (n.puts[i] == 1) {
            cout << i << "번, ";
        }
    } cout << endl;
    contMout("n.nutSum:", n.nutSum);
    varMout("n.cost", n.cost);
    varMout("n.gsb", n.gsb);
    varout("==========노드출력끝==============");
}

vector<int> criteria(4);
vector<vector<int>> diets; // 0순번/영양소4개/5가격/6영양분합/7gsb
priority_queue<Node> pq;
vector<Node> solNodes;
set<vector<int>> finishedSet;

bool cmp(const vector<int> &v1, const vector<int> &v2) {
    if (v1[7] == v2[7]) { //가성비 같으면
        return v1[5] < v2[5]; // 가격 낮은 대로
    } else
        return v1[7] > v2[7]; // 가성비 큰 순서대로
}

void printPq() {
    priority_queue<Node> pq2 = pq;
    cout << "가성비 좋은거부터 하나씩 뽑아 내어 봅시다.\n" ;
    while ( !pq2.empty() ) {
        Node n = pq2.top();
        cout << "들어간 노드들:";
        contout(n.puts);
        pq2.pop();
    }
}



int main() {
    int k;
    cin >> k;
    int minCost = 500 * k; // 최대 가격 * 재료 갯수. 가격 다 합친거
    for (int i = 0; i < 4; i++) {
        cin >> criteria[i];
    }
    for (int i = 0; i < k; i++) {
        vector<int> row(8); // 0순번/영양소4개/5가격/6영양분합/7GASUNGBI
        row[0] = i+1; // 순번
        for (int j = 1; j < 6; j++) {
            cin >> row[j];
        }
        cout << endl;
        diets.push_back(row);
    }
    // 영양분합 + GASUNGBI
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

    LINE;
    contMout("criteria", criteria);
    LINE;
    cout << "0순번/영양소4개/5가격/6영양분합/7가성비\n";
    for (int i = 0; i < k; i++) {
        contout(diets[i]);
    }
    LINE;
    sort(diets.begin(), diets.end(), cmp);
    cout << "정렬 후 (가성비 순 -> 가격 순\n";
    for (int i = 0; i < k; i++) {
        contout(diets[i]);
    }
    LINE;
    // 코딩 시작
    varout("3. 일단 pq에 다 넣는 작업=============");
    for (auto diet: diets) { //일단 pq에 다 넣는 작업
        // 넣은 재료
        vector<int> puts(k + 1); //1번 순번의 재료는 index 1에 저장하기 위해..1 해놓음. 즉 0번쨰 index값은 더미값
        puts[diet[0]] = 1; // 해당하는 순번 재료를 넣음 표시
//        contout(puts);
        // 각 영양분합
        vector<int> nutSum(4);
        for (int i = 1; i < 5; i++) {
            nutSum[i-1] = diet[i];
        }
//        contout(nutSum);
        Node node(puts, nutSum, diet[5], diet[7]);
        pq.push(node);
    }
    printPq();

    varout("4. 본 작업 ================================================");
    while(!pq.empty()) {
        Node prom = pq.top(); //프로미싱 노드
        cout << ("********** 프로미싱 노드 POPPED prom:");
        printNode(prom);
        pq.pop();
//        vector<int> promPuts = prom.puts;

        for (int i = 0; i < k; i++) { // diets를 돌면서
            vector<int> diet = diets[i];
            int ingNum = diet[0]; //가장 우선순위가 높은 재료의 순번
            int solFlag = 0;

            if (prom.puts[ingNum] == 0) {// 해당 노드에 안 넣은 것이 있으면
                printf("%d 번 집어넣음 !\n", ingNum);
                prom.puts[ingNum] = 1; //집어넘
                // 이미 했던 집합인지 확인
                auto pos = finishedSet.find(prom.puts);
                if (pos == finishedSet.end()) {
                    cout << "Not found" << endl;
                    finishedSet.insert(prom.puts);
                } else {
                    cout << "Found" << endl;
                    prom.puts[ingNum] = 0; //복구
                    continue;
                }
//
//                cout << "finishedSet 출력 ==\n";
//                for (auto v: finishedSet) {
//                    cout << "|| ";
//                    contout(v);
//                }



                for (int j = 0; j < 4; j++) {
                    prom.nutSum[j] += diet[j+1]; //영양분 업데이트
                    //영양분 조건 만족하는지 확인
                    if (prom.nutSum[j] >= criteria[j]) {
                        solFlag++;
                    }
                }
                prom.cost += diet[5];
                prom.gsb += diet[7];
                printNode(prom);
                if (solFlag == 4) { // 해 만족
                    cout << ("해만족!!!\n");
                    if (prom.cost < minCost) {
                        minCost = prom.cost;
                        solNodes.clear(); // 더 작은해가 나타났으므로 여태까지의 솔루션 집합 비움
                        solNodes.push_back(prom);
                    } else if (prom.cost == minCost) {
                        solNodes.push_back(prom);
                    }
                    // 해를 만족시킨 지금 노드를 .. 다시뻄. finishedSet엔 고대로 들어가있으니까 체크 안하지 않나?
                    prom.puts[ingNum] = 0; // 다시뺴고 push..

                }

                pq.push(prom);
                break;
            }
        }
    }

    // 결과
    varout("5. 결과 ================================================");

    for (auto node: solNodes) {
        printNode(node);
    }

    if (solNodes.size() == 1) {
        for (int i = 1; i < k+1; i++) {
            if (solNodes[0].puts[i] == 1) cout << i << ' ';
        }
    } else if (solNodes.size() == 0) {
        cout << "0";
    } else if (solNodes.size() > 1) {
        // 영양분 총합 더 높은것
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
            varMout("allNutSum ", allNutSum );
            if (allNutSum > maxAllNutSum) {
                strPuts.clear();
                maxAllNutSum = allNutSum;
                idx = i;
            } else if (allNutSum == maxAllNutSum) {
//                puts.push_back(solNodes[i].puts);
                string s;
                for (int j = 0; j < solNodes[i].puts.size(); j++) {
                    s += to_string(solNodes[i].puts[j]);
                }
                cout << s<<endl;
                strPuts.push_back(s);
            }
        }
        if (strPuts.size() > 0) { // 영양분 총합 같은게 여러개 일 경우 인덱스 가장 빠른거 출력
            cout << "가격, 영양분 총합 같은게 여러개 일 경우 인덱스 가장 빠른거 출력\n";
            for (auto s: strPuts) {
                cout << s << endl;
            }
            auto it = min_element(strPuts.begin(), strPuts.end());
            for (int i = 1; i < k+1; i++) {
                if ((*it)[i] == '1') cout << i << ' ';
            }

        } else { // 영양분 총합이 가장 높은거 출력
            for (int i = 1; i < k+1; i++) {
                if (solNodes[idx].puts[i] == 1) cout << i << ' ';
            }
        }
    }





    return 0;
}
