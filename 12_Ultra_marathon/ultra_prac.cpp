#include "../smtool.h"
#include <iostream>
#include <set>
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
vector<vector<Edge>> graph(26);
vector<vector<Edge>> graphBfs(26);

void printG() {
    LINE;
    for (int i = 0; i < graph.size(); i++) {
        cout << graph[i].size() << endl;
        for (Edge e: graph[i]) {
            cout << i << ", " << (char)(i + 'a');
            printf("- %c, %d\n", (char)e.dest + 'a', e.weight);
        }
    }
    ENDL;
}

bool cmp(const Edge &edge1, const Edge &edge2) {
    if (edge1.weight == edge2.weight) {
        return edge1.dest < edge2.dest; // alphabetic order
    } else {
        return edge1.weight > edge2.weight; // weight big -> small
    }
}
int dist = 0;
int maxDist = 0;
int finish = 0;
int restore = 0;
int turn = 1;
deque<char> dq;
vector<string> result;
vector<int> dists;

queue <int> que;

// bool bfs(int index, int destIndex) {
bool bfs(int index) {
    bool visitedBfs[27] = {false, };

	cout << (char)(index + 'A');
	visited[index] = true;
	que.push(index);
	int nowNum;
	while(!que.empty()){
		nowNum = que.front();
		que.pop();

		for (int i = 0; i < graphBfs[nowNum].size(); i++) {
			if (visited[graphBfs[nowNum][i].dest] == false) {
                dist += graphBfs[index][i].weight;
                cout << "dist updated: " << dist << endl;
				cout << (char)(graphBfs[nowNum][i].dest + 'A');
				visited[graphBfs[nowNum][i].dest] = true;
				que.push(graphBfs[nowNum][i].dest);
			}
		}
	}
    if (visitedBfs[0] == false) { // a is not connected
        varout("연결돼있지 않음");
        return false;
    } else {
        varout("연결돼있음");
        return true;
    }
}

void dfs(int index) {
//    cout << (char) (index + 'a') << ' ';
    visited[index] = true;
    dq.push_back((char)(index + 'a'));
    cout << "^^" << graph[index].size() << endl;


    for (int i = 0; i < graph[index].size(); i++) {
        int destIndex = graph[index][i].dest;
        printf("(%c - %c, %d)\n", (char) (index + 'a'), (char) destIndex + 'a', graph[index][i].weight);
        if (destIndex == 0) {
            dist = dist + graph[index][i].weight;
            if (dist > maxDist) maxDist = dist;

            string outputString(dq.begin(), dq.end());
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
            cout << "completed!!: " << outputString << "\n";
            result.push_back(outputString);
        }
        if (visited[destIndex] == false) {
            dist += graph[index][i].weight;
            cout << "dist updated: " << dist << endl;

            // erase edge
            graphBfs[index].erase(graphBfs[index].begin() + i);
            graphBfs[destIndex].erase(remove_if(graphBfs[destIndex].begin(), graphBfs[destIndex].end(), [&index](auto x) -> bool { return x.dest == index; }), graphBfs[destIndex].end());

            bool isConnected = bfs(destIndex);
            if (!isConnected)
                return;
            else 
                graphBfs[index].push_back(Edge(destIndex, graph[index][i].weight));
                graphBfs[destIndex].push_back(Edge(index, graph[index][i].weight));
            


            dfs(destIndex);
        }
        if (restore == 1) {
            restore = 0;
            dist -= graph[index][i].weight;
            printf("%c's dist restored: %d\n", (char)(index + 'a'), dist);
        }
        if (i+1 == graph[index].size()) {// if couldn't find to go
            visited[index] = false;
            dq.pop_back();
            printf("%c's visited restored\n", (char)(index + 'a'));
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

    printG();

    dfs(0);

    cout << maxDist << endl;
   
    return 0;
}
