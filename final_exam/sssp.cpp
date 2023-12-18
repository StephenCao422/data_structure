#include <iostream>

using namespace std;

vector<Vertex> shortestPath(Graph& g, Vertex start, Vertex destination) {
        vector<Vertex> vertices = g.getVertices();
        vector<Edge> edges = g.getEdges();
        
        map<Vertex, int> dist;
        for (Vertex& v: vertices) {
            dist[v] = INT_MAX;
        }
        
        map<Vertex, Vertex> pred;
        map<Vertex, bool> unvisited;
        //{distance, Vertex}
        priority_queue<pair<int, Vertex>, vector<pair<int, Vertex>, greater<pair<int, Vertex>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            unvisited[u] = false;
            vector<Vertex> neighbors = g.getAdjacent(u);

            for (Vertex& v: neighbors) {
                Edge edge = g.getEdge(u, v);
                int weight = edge->weight;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pred[v] = vertices[u];
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[destination] == INT_MAX) {
            return {}; 
        }

        vector<Vertex> path;
        for (Vertex v = destination; v != start; v = pred[v]) {
            path.push_back(v);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        return path;
}