#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int minDistance(vector<int>& dist, vector<bool>& sptSet, int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(vector<int>& dist, int V) {
    cout << "Vertex \tDistance from Source\n";
    for (int i = 0; i < V; i++)
        cout << i << " \t" << dist[i] << "\n";
}

void dijkstra(vector<vector<int>>& graph, int src, int V) {
    vector<int> dist(V, INT_MAX);
    vector<bool> sptSet(V, false);

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist, V);
}
