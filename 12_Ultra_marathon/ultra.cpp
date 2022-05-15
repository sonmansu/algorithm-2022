#include <bits/stdc++.h>
using namespace std;

stack<char> st;

bool visited[27] = {false, };
//int visited[27] = {0, };

class Edge {
public:
    int dest;
    int weight;

    Edge(char dest_, int weight_) {
        dest = dest_;
        weight = weight_;
    }
};
bool cmp(const Edge &edge1, const Edge &edge2) {
    if (edge1.weight == edge2.weight) {
        return edge1.dest < edge2.dest; // alphabetic order
    } else {
        return edge1.weight > edge2.weight; // weight big -> small
    }
}

vector<vector<Edge>> graph(26);

int dist = 0;
int restore = 0;
vector<int> dists;
void dfs(int index) {
    visited[index] = true;
    for (int i = 0; i < graph[index].size(); i++) {
        if (graph[index][i].dest == 0) {
            dists.push_back(dist + graph[index][i].weight);
        }
        if (visited[graph[index][i].dest] == false) {
            dist += graph[index][i].weight;
            dfs(graph[index][i].dest);
        }
        if (restore == 1) {
            restore = 0;
            dist -= graph[index][i].weight;
        }
        if (i+1 == graph[index].size()) {// if couldn't find to go
            visited[index] = false;
            restore = 1;
        }

    }


}
int main() {
    int N, M, weight; // vertex num, edge num
    char c1, c2;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        cin >> c1 >> c2 >> weight;

        graph[c1 - 'a'].push_back(Edge(c2 - 'a', weight));
        graph[c2 - 'a'].push_back(Edge(c1 - 'a', weight));
    }


    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            sort(graph[i].begin(), graph[i].end(), cmp);
        }
    }

    dfs(0);

    auto it = max_element(dists.begin(), dists.end());
    cout << *it;

    return 0;
}
