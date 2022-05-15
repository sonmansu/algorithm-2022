#include <bits/stdc++.h>
using namespace std;


bool visited[27] = {false, };

class Edge {
  public:
    int dest;
    int weight;

    Edge(char dest_, int weight_) {
        dest = dest_;
        weight = weight_;
    }
};
vector<vector<Edge>> graph(26);
vector<vector<Edge>> graphBfs(26);

bool cmp(const Edge &edge1, const Edge &edge2) {
    if (edge1.weight == edge2.weight) {
        return edge1.dest < edge2.dest; // alphabetic order
    } else {
        return edge1.weight > edge2.weight; // weight big -> small
    }
}
int dist = 0;
int maxDist = 0;
int restore = 0;
vector<int> dists;
queue <int> que;



bool bfs(int index) { // input: destIndex
    bool visitedBfs[27];
    copy(visited, visited + 27, visitedBfs);

    visitedBfs[0] = false; // 'a' is not visited

    visitedBfs[index] = true;
    que.push(index);
    int nowNum;
    while(!que.empty()) {
        nowNum = que.front();
        que.pop();

        for (int i = 0; i < graphBfs[nowNum].size(); i++) {
            if (visitedBfs[graphBfs[nowNum][i].dest] == false) {
                visitedBfs[graphBfs[nowNum][i].dest] = true;
                que.push(graphBfs[nowNum][i].dest);
            }
        }
    }
    if (visitedBfs[0] == false) { // a is not connected
        return false;
    } else {
        return true;
    }
}

void dfs(int index) {
    visited[index] = true;


    for (int i = 0; i < graph[index].size(); i++) {
        int destIndex = graph[index][i].dest;
        if (destIndex == 0) {
            if (dist + graph[index][i].weight > maxDist) maxDist = dist + graph[index][i].weight;
        }
        if (visited[destIndex] == false) {
            bool isConnected = bfs(destIndex);
            if (isConnected) {
                dist += graph[index][i].weight;
                dfs(destIndex);
            } else {}
        }
        if (restore == 1) {
            restore = 0;
            dist -= graph[index][i].weight;
        }
        if (i+1 == graph[index].size()) {// if couldn't find to go
            visited[index] = false;

            if (index == 0) {
                return;
            }

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
    graphBfs = graph;
    dfs(0);

    cout << maxDist << endl;

    return 0;
}
