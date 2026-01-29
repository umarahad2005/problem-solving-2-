/*
 * Dijkstra's Algorithm - Problem 1
 * Network Delay Time (LeetCode 743)
 * 
 * Problem: You have a network of n nodes labeled from 1 to n. You are given times, 
 * a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the 
 * source node, vi is the target node, and wi is the time it takes for a signal to 
 * travel from source to target. Given a starting node k, return the minimum time 
 * it takes for all n nodes to receive the signal. If impossible, return -1.
 */

#include<iostream>
#include<vector>
#include<climits>
using namespace std;

class DijkstraNetworkDelay {
    static const int INF = INT_MAX;
    
public:
    // Dijkstra's algorithm using adjacency matrix
    int networkDelayTime(int n, vector<vector<int>>& times, int k) {
        // Create adjacency matrix
        vector<vector<int>> graph(n + 1, vector<int>(n + 1, INF));
        
        // Initialize self-loops to 0
        for(int i = 0; i <= n; i++) {
            graph[i][i] = 0;
        }
        
        // Fill in edges
        for(int i = 0; i < times.size(); i++) {
            int u = times[i][0];
            int v = times[i][1];
            int w = times[i][2];
            graph[u][v] = w;
        }
        
        // Distance array
        vector<int> dist(n + 1, INF);
        vector<bool> visited(n + 1, false);
        dist[k] = 0;
        
        // Dijkstra's algorithm
        for(int count = 0; count < n; count++) {
            // Find minimum distance vertex not yet processed
            int u = -1;
            int minDist = INF;
            
            for(int v = 1; v <= n; v++) {
                if(!visited[v] && dist[v] < minDist) {
                    minDist = dist[v];
                    u = v;
                }
            }
            
            if(u == -1) break; // No reachable unvisited vertex
            
            visited[u] = true;
            
            // Update distances of adjacent vertices
            for(int v = 1; v <= n; v++) {
                if(!visited[v] && graph[u][v] != INF && dist[u] != INF) {
                    if(dist[u] + graph[u][v] < dist[v]) {
                        dist[v] = dist[u] + graph[u][v];
                    }
                }
            }
        }
        
        // Find maximum distance (time for all nodes to receive signal)
        int maxTime = 0;
        for(int i = 1; i <= n; i++) {
            if(dist[i] == INF) return -1; // Node unreachable
            maxTime = max(maxTime, dist[i]);
        }
        
        return maxTime;
    }
    
    void printShortestPaths(int n, vector<int>& dist, int source) {
        cout << "\nShortest paths from node " << source << ":" << endl;
        for(int i = 1; i <= n; i++) {
            cout << "  To node " << i << ": ";
            if(dist[i] == INF) cout << "UNREACHABLE";
            else cout << dist[i];
            cout << endl;
        }
    }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Assignment 4 - Dijkstra Problem 1: Network Delay Time" << endl;
    cout << "======================================================" << endl;
    
    DijkstraNetworkDelay solver;
    int choice;
    
    while(true) {
        cout << "\n1. Run Example 1 (n=4, k=2)" << endl;
        cout << "2. Run Example 2 (n=2, k=1)" << endl;
        cout << "3. Custom Input" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if(choice == 1) {
            // Example: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
            cout << "\nExample 1:" << endl;
            cout << "Network: 4 nodes" << endl;
            cout << "Edges: 2->1 (1), 2->3 (1), 3->4 (1)" << endl;
            cout << "Source: Node 2" << endl;
            
            vector<vector<int>> times = {{2,1,1}, {2,3,1}, {3,4,1}};
            int result = solver.networkDelayTime(4, times, 2);
            
            cout << "\nOutput: " << result << endl;
            cout << "Explanation: Signal reaches all nodes in 2 time units." << endl;
        }
        else if(choice == 2) {
            // Example: times = [[1,2,1]], n = 2, k = 1
            cout << "\nExample 2:" << endl;
            cout << "Network: 2 nodes" << endl;
            cout << "Edges: 1->2 (1)" << endl;
            cout << "Source: Node 1" << endl;
            
            vector<vector<int>> times = {{1,2,1}};
            int result = solver.networkDelayTime(2, times, 1);
            
            cout << "\nOutput: " << result << endl;
        }
        else if(choice == 3) {
            int n, m, k;
            cout << "Enter number of nodes: ";
            cin >> n;
            cout << "Enter number of edges: ";
            cin >> m;
            cout << "Enter source node: ";
            cin >> k;
            
            vector<vector<int>> times;
            cout << "Enter edges (u v w - from u to v with weight w):" << endl;
            for(int i = 0; i < m; i++) {
                int u, v, w;
                cout << "Edge " << (i+1) << ": ";
                cin >> u >> v >> w;
                times.push_back({u, v, w});
            }
            
            int result = solver.networkDelayTime(n, times, k);
            
            if(result == -1) {
                cout << "\nOutput: -1 (Not all nodes are reachable)" << endl;
            } else {
                cout << "\nOutput: " << result << endl;
                cout << "Minimum time for signal to reach all nodes: " << result << endl;
            }
        }
        else if(choice == 4) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
