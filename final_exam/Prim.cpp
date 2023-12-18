#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> iPair;

class Graph {
public:
    int V;
    vector<vector<iPair> > adj;

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    void primMST(int src) {
        priority_queue<iPair, vector<iPair>, greater<iPair> > pq;
        vector<int> key(V, INT_MAX);
        vector<int> parent(V, -1);
        vector<bool> inMST(V, false);

        pq.push(make_pair(0, src));
        key[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            for (auto i : adj[u]) {
                int v = i.first;
                int weight = i.second;

                if (!inMST[v] && key[v] > weight) {
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }

        for (int i = 1; i < V; ++i)
            cout << parent[i] << " - " << i << endl;
    }
};

int main() {
    int V = 5;
    Graph g(V);

    // add edges
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);

    g.primMST(0);

    return 0;
}
