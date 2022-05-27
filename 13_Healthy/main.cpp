#include "../smtool.h"
#include <iostream>
#include <set>
#include <bits/stdc++.h>
using namespace std;
#define MAX_GASUNGBI  100000 // (each nutrients max:)25000 * 4

class Node {
  public:
    vector<int> puts; // ��� ������ŭ
    vector<int> nutSum; // ����� ��
    int cost; //����
    int gsb; // ������
    // ������
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
    // �׳� ������ ��� ���� �й����� �й��� �������� Top �� ���� �Ѵ�
    bool operator<(const Node node) const {
        //���� ���� ���ҋ� ���� ������ ��ȯ �ϴ°� ������
        return (this->cost > node.cost);
//        if (this->gsb == node.gsb) {
//            return (this->cost > node.cost); // ���� �������
//        } else
//            return (this->gsb < node.gsb); // ������ ū �������
    }
};
void printNode(const Node &n) {
    varout("==========�����½���=============");
//    contMout("n.puts:", n.puts);
    cout << "n.puts: ";
    for (int i = 0; i < (n.puts).size(); i++) {
        if (n.puts[i] == 1) {
            cout << i << "��, ";
        }
    } cout << endl;
    contMout("n.nutSum:", n.nutSum);
    varMout("n.cost", n.cost);
    varMout("n.gsb", n.gsb);
    varout("==========�����³�==============");
}

vector<int> criteria(4);
vector<vector<int>> diets; // 0����/�����4��/5����/6�������/7gsb
priority_queue<Node> pq;
vector<Node> solNodes;
set<vector<int>> finishedSet;

bool cmp(const vector<int> &v1, const vector<int> &v2) {
    if (v1[7] == v2[7]) { //������ ������
        return v1[5] < v2[5]; // ���� ���� ���
    } else
        return v1[7] > v2[7]; // ������ ū �������
}

void printPq() {
    priority_queue<Node> pq2 = pq;
    cout << "������ �����ź��� �ϳ��� �̾� ���� ���ô�.\n" ;
    while ( !pq2.empty() ) {
        Node n = pq2.top();
        cout << "�� ����:";
        contout(n.puts);
        pq2.pop();
    }
}



int main() {
    int k;
    cin >> k;
    int minCost = 500 * k; // �ִ� ���� * ��� ����. ���� �� ��ģ��
    for (int i = 0; i < 4; i++) {
        cin >> criteria[i];
    }
    for (int i = 0; i < k; i++) {
        vector<int> row(8); // 0����/�����4��/5����/6�������/7GASUNGBI
        row[0] = i+1; // ����
        for (int j = 1; j < 6; j++) {
            cin >> row[j];
        }
        cout << endl;
        diets.push_back(row);
    }
    // ������� + GASUNGBI
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
    cout << "0����/�����4��/5����/6�������/7������\n";
    for (int i = 0; i < k; i++) {
        contout(diets[i]);
    }
    LINE;
    sort(diets.begin(), diets.end(), cmp);
    cout << "���� �� (������ �� -> ���� ��\n";
    for (int i = 0; i < k; i++) {
        contout(diets[i]);
    }
    LINE;
    // �ڵ� ����
    varout("3. �ϴ� pq�� �� �ִ� �۾�=============");
    for (auto diet: diets) { //�ϴ� pq�� �� �ִ� �۾�
        // ���� ���
        vector<int> puts(k + 1); //1�� ������ ���� index 1�� �����ϱ� ����..1 �س���. �� 0���� index���� ���̰�
        puts[diet[0]] = 1; // �ش��ϴ� ���� ��Ḧ ���� ǥ��
//        contout(puts);
        // �� �������
        vector<int> nutSum(4);
        for (int i = 1; i < 5; i++) {
            nutSum[i-1] = diet[i];
        }
//        contout(nutSum);
        Node node(puts, nutSum, diet[5], diet[7]);
        pq.push(node);
    }
    printPq();

    varout("4. �� �۾� ================================================");
    while(!pq.empty()) {
        Node prom = pq.top(); //���ι̽� ���
        cout << ("********** ���ι̽� ��� POPPED prom:");
        printNode(prom);
        pq.pop();
//        vector<int> promPuts = prom.puts;

        for (int i = 0; i < k; i++) { // diets�� ���鼭
            vector<int> diet = diets[i];
            int ingNum = diet[0]; //���� �켱������ ���� ����� ����
            int solFlag = 0;

            if (prom.puts[ingNum] == 0) {// �ش� ��忡 �� ���� ���� ������
                printf("%d �� ������� !\n", ingNum);
                prom.puts[ingNum] = 1; //�����
                // �̹� �ߴ� �������� Ȯ��
                auto pos = finishedSet.find(prom.puts);
                if (pos == finishedSet.end()) {
                    cout << "Not found" << endl;
                    finishedSet.insert(prom.puts);
                } else {
                    cout << "Found" << endl;
                    prom.puts[ingNum] = 0; //����
                    continue;
                }
//
//                cout << "finishedSet ��� ==\n";
//                for (auto v: finishedSet) {
//                    cout << "|| ";
//                    contout(v);
//                }



                for (int j = 0; j < 4; j++) {
                    prom.nutSum[j] += diet[j+1]; //����� ������Ʈ
                    //����� ���� �����ϴ��� Ȯ��
                    if (prom.nutSum[j] >= criteria[j]) {
                        solFlag++;
                    }
                }
                prom.cost += diet[5];
                prom.gsb += diet[7];
                printNode(prom);
                if (solFlag == 4) { // �� ����
                    cout << ("�ظ���!!!\n");
                    if (prom.cost < minCost) {
                        minCost = prom.cost;
                        solNodes.clear(); // �� �����ذ� ��Ÿ�����Ƿ� ���±����� �ַ�� ���� ���
                        solNodes.push_back(prom);
                    } else if (prom.cost == minCost) {
                        solNodes.push_back(prom);
                    }
                    // �ظ� ������Ų ���� ��带 .. �ٽÖM. finishedSet�� ���� �������ϱ� üũ ������ �ʳ�?
                    prom.puts[ingNum] = 0; // �ٽÕ��� push..

                }

                pq.push(prom);
                break;
            }
        }
    }

    // ���
    varout("5. ��� ================================================");

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
        // ����� ���� �� ������
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
        if (strPuts.size() > 0) { // ����� ���� ������ ������ �� ��� �ε��� ���� ������ ���
            cout << "����, ����� ���� ������ ������ �� ��� �ε��� ���� ������ ���\n";
            for (auto s: strPuts) {
                cout << s << endl;
            }
            auto it = min_element(strPuts.begin(), strPuts.end());
            for (int i = 1; i < k+1; i++) {
                if ((*it)[i] == '1') cout << i << ' ';
            }

        } else { // ����� ������ ���� ������ ���
            for (int i = 1; i < k+1; i++) {
                if (solNodes[idx].puts[i] == 1) cout << i << ' ';
            }
        }
    }





    return 0;
}
