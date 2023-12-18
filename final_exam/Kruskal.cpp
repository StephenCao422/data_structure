#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int src, dest, weight;
};

class Graph {
public:
    int V, E;
    vector<Edge> edges;

    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w, int count) {
        edges[count].src = u;
        edges[count].dest = v;
        edges[count].weight = w;
    }

    int find(vector<int>& parent, int i) {
        if (parent[i] == -1)
            return i;
        return find(parent, parent[i]);
    }

    void Union(vector<int>& parent, int x, int y) {
        int xset = find(parent, x);
        int yset = find(parent, y);
        if (xset != yset) {
            parent[xset] = yset;
       
        }
    }
    
    void KruskalMST() {
        vector<Edge> result(V);
        int e = 0;
        int i = 0;

        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
        });

        vector<int> parent(V, -1);

        while (e < V - 1 && i < E) {
            Edge next_edge = edges[i++];
            int x = find(parent, next_edge.src);
            int y = find(parent, next_edge.dest);

            if (x != y) {
                result[e++] = next_edge;
                Union(parent, x, y);
            }
        }

        cout << "Following are the edges in the constructed MST\n";
        for (i = 0; i < e; ++i)
            cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;
    }
};

