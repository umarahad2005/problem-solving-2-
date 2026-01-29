/*
 * Bellman-Ford Algorithm - Problem 1
 * Detect Negative Cycle and Find Shortest Paths (GeeksforGeeks)
 * 
 * Problem: Given a weighted directed graph, find shortest distances from source 
 * to all vertices. The graph may contain negative weight edges. Bellman-Ford can 
 * also detect negative weight cycles, which Dijkstra's algorithm cannot handle.
 */

#include<iostream>
#include<vector>
#include<climits>
using namespace std;

struct Edge {
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

class BellmanFordNegativeCycle {
    static const int INF = INT_MAX;
    
public:
    // Bellman-Ford algorithm with negative cycle detection
    bool bellmanFord(int V, vector<Edge>& edges, int src, vector<int>& dist, vector<int>& parent) {
        // Initialize distances
        dist.assign(V, INF);
        parent.assign(V, -1);
        dist[src] = 0;
        
        // Relax all edges V-1 times
        for(int i = 0; i < V - 1; i++) {
            bool updated = false;
            
            for(int j = 0; j < edges.size(); j++) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int w = edges[j].weight;
                
                if(dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    updated = true;
                }
            }
            
            // Early termination if no updates
            if(!updated) break;
        }
        
        // Check for negative cycle (V-th iteration)
        for(int j = 0; j < edges.size(); j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;
            
            if(dist[u] != INF && dist[u] + w < dist[v]) {
                return true; // Negative cycle detected
            }
        }
        
        return false; // No negative cycle
    }
    
    void printPath(int dest, vector<int>& parent) {
        if(dest == -1) return;
        
        vector<int> path;
        int current = dest;
        while(current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        
        for(int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
            if(i > 0) cout << " -> ";
        }
    }
    
    void solve(int V, vector<Edge>& edges, int src) {
        vector<int> dist, parent;
        
        cout << "\n=== BELLMAN-FORD ALGORITHM ===" << endl;
        cout << "Source vertex: " << src << endl;
        cout << "Number of vertices: " << V << endl;
        cout << "Number of edges: " << edges.size() << endl;
        
        bool hasNegativeCycle = bellmanFord(V, edges, src, dist, parent);
        
        if(hasNegativeCycle) {
            cout << "\n*** NEGATIVE CYCLE DETECTED! ***" << endl;
            cout << "Shortest paths are undefined." << endl;
        } else {
            cout << "\nNo negative cycle found." << endl;
            cout << "\nShortest distances from vertex " << src << ":" << endl;
            
            for(int i = 0; i < V; i++) {
                cout << "  Vertex " << i << ": ";
                if(dist[i] == INF) {
                    cout << "UNREACHABLE";
                } else {
                    cout << dist[i] << " | Path: ";
                    printPath(i, parent);
                }
                cout << endl;
            }
        }
    }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Assignment 4 - Bellman-Ford Problem 1: Negative Cycle Detection" << endl;
    cout << "================================================================" << endl;
    
    BellmanFordNegativeCycle solver;
    int choice;
    
    while(true) {
        cout << "\n1. Example without negative cycle" << endl;
        cout << "2. Example with negative cycle" << endl;
        cout << "3. Example with negative weights (no cycle)" << endl;
        cout << "4. Custom Input" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if(choice == 1) {
            cout << "\nExample: Graph without negative cycle" << endl;
            cout << "Edges: 0->1(4), 0->2(5), 1->2(-3), 2->3(4)" << endl;
            
            vector<Edge> edges;
            edges.push_back(Edge(0, 1, 4));
            edges.push_back(Edge(0, 2, 5));
            edges.push_back(Edge(1, 2, -3));
            edges.push_back(Edge(2, 3, 4));
            
            solver.solve(4, edges, 0);
        }
        else if(choice == 2) {
            cout << "\nExample: Graph WITH negative cycle" << endl;
            cout << "Edges: 0->1(1), 1->2(-1), 2->0(-1)" << endl;
            cout << "Cycle: 0 -> 1 -> 2 -> 0 with total weight = -1" << endl;
            
            vector<Edge> edges;
            edges.push_back(Edge(0, 1, 1));
            edges.push_back(Edge(1, 2, -1));
            edges.push_back(Edge(2, 0, -1));
            
            solver.solve(3, edges, 0);
        }
        else if(choice == 3) {
            cout << "\nExample: Complex graph with negative weights (no cycle)" << endl;
            cout << "5 vertices with mixed positive and negative edges" << endl;
            
            vector<Edge> edges;
            edges.push_back(Edge(0, 1, -1));
            edges.push_back(Edge(0, 2, 4));
            edges.push_back(Edge(1, 2, 3));
            edges.push_back(Edge(1, 3, 2));
            edges.push_back(Edge(1, 4, 2));
            edges.push_back(Edge(3, 2, 5));
            edges.push_back(Edge(3, 1, 1));
            edges.push_back(Edge(4, 3, -3));
            
            solver.solve(5, edges, 0);
        }
        else if(choice == 4) {
            int V, E, src;
            cout << "Enter number of vertices: ";
            cin >> V;
            cout << "Enter number of edges: ";
            cin >> E;
            cout << "Enter source vertex: ";
            cin >> src;
            
            vector<Edge> edges;
            cout << "Enter edges (src dest weight):" << endl;
            for(int i = 0; i < E; i++) {
                int s, d, w;
                cout << "Edge " << (i+1) << ": ";
                cin >> s >> d >> w;
                edges.push_back(Edge(s, d, w));
            }
            
            solver.solve(V, edges, src);
        }
        else if(choice == 5) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
