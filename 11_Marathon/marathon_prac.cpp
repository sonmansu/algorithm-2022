#include "../smtool.h"
#include <iostream>
#include <set>
using namespace std;

// multimap<char, char, int> tree;
// multimap<pair<char, char>, int> tree;
multimap<char, pair<char, int>> tree;

void printTree() {
    for (auto it = tree.begin(); it != tree.end(); it++) {
        cout << it->first << " - " << (it->second).first << ", "<< (it->second).second << endl;
    }
}

int main() {
    int N, M, weight; // vertex num, edge num
    char c1, c2;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        cin >> c1 >> c2 >> weight;
        // tree.insert(make_pair(make_pair(c1, c2), weight));
        tree.insert(make_pair(c1, make_pair(c2, weight)));
        tree.insert(make_pair(c2, make_pair(c1, weight)));
    }
    printTree();
    // auto p = tree.equal_range('a');
    // for (auto it = p.first; it != p.second; it++) {
    //     cout << it->first << " , " << (it->second).first << ", "<< (it->second).second << endl;
    // }


    

    return 0;
}