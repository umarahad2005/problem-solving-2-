/*
 * Dijkstra's Algorithm - Problem 2
 * Cheapest Flights Within K Stops (LeetCode 787 - Modified)
 * 
 * Problem: There are n cities connected by flights. Given flights where 
 * flights[i] = [from, to, price], find the cheapest price from src to dst.
 * This is a classic shortest path problem solved using Dijkstra's algorithm.
 */

#include<iostream>
#include<vector>
#include<climits>
using namespace std;

class DijkstraCheapestFlight {
    static const int INF = INT_MAX;
    
public:
    // Find cheapest path using Dijkstra's algorithm
    void findCheapestPath(int n, vector<vector<int>>& flights, int src, int dst) {
        // Create adjacency matrix
        vector<vector<int>> graph(n, vector<int>(n, INF));
        
        for(int i = 0; i < n; i++) {
            graph[i][i] = 0;
        }
        
        for(int i = 0; i < flights.size(); i++) {
            int from = flights[i][0];
            int to = flights[i][1];
            int price = flights[i][2];
            graph[from][to] = price;
        }
        
        // Distance and parent arrays
        vector<int> dist(n, INF);
        vector<int> parent(n, -1);
        vector<bool> visited(n, false);
        dist[src] = 0;
        
        // Dijkstra's algorithm
        for(int count = 0; count < n; count++) {
            int u = -1;
            int minDist = INF;
            
            for(int v = 0; v < n; v++) {
                if(!visited[v] && dist[v] < minDist) {
                    minDist = dist[v];
                    u = v;
                }
            }
            
            if(u == -1) break;
            visited[u] = true;
            
            for(int v = 0; v < n; v++) {
                if(!visited[v] && graph[u][v] != INF && dist[u] != INF) {
                    if(dist[u] + graph[u][v] < dist[v]) {
                        dist[v] = dist[u] + graph[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
        
        // Output results
        cout << "\n=== SHORTEST PATH RESULTS ===" << endl;
        cout << "From city " << src << " to city " << dst << ":" << endl;
        
        if(dist[dst] == INF) {
            cout << "No path exists!" << endl;
        } else {
            cout << "Cheapest price: $" << dist[dst] << endl;
            
            // Reconstruct path
            cout << "Path: ";
            vector<int> path;
            int current = dst;
            while(current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            
            for(int i = path.size() - 1; i >= 0; i--) {
                cout << path[i];
                if(i > 0) cout << " -> ";
            }
            cout << endl;
        }
        
        // Print all shortest paths from source
        cout << "\nAll shortest paths from city " << src << ":" << endl;
        for(int i = 0; i < n; i++) {
            cout << "  To city " << i << ": ";
            if(dist[i] == INF) cout << "UNREACHABLE";
            else cout << "$" << dist[i];
            cout << endl;
        }
    }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Assignment 4 - Dijkstra Problem 2: Cheapest Flights" << endl;
    cout << "====================================================" << endl;
    
    DijkstraCheapestFlight solver;
    int choice;
    
    while(true) {
        cout << "\n1. Run Example 1 (4 cities)" << endl;
        cout << "2. Run Example 2 (5 cities)" << endl;
        cout << "3. Custom Input" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if(choice == 1) {
            cout << "\nExample 1: 4 cities" << endl;
            cout << "Flights:" << endl;
            cout << "  0 -> 1 ($100)" << endl;
            cout << "  1 -> 2 ($100)" << endl;
            cout << "  2 -> 0 ($100)" << endl;
            cout << "  1 -> 3 ($600)" << endl;
            cout << "  2 -> 3 ($200)" << endl;
            
            vector<vector<int>> flights = {
                {0, 1, 100}, {1, 2, 100}, {2, 0, 100}, 
                {1, 3, 600}, {2, 3, 200}
            };
            solver.findCheapestPath(4, flights, 0, 3);
        }
        else if(choice == 2) {
            cout << "\nExample 2: 5 cities" << endl;
            cout << "Flights:" << endl;
            cout << "  0 -> 1 ($50)" << endl;
            cout << "  0 -> 2 ($200)" << endl;
            cout << "  1 -> 2 ($40)" << endl;
            cout << "  1 -> 3 ($70)" << endl;
            cout << "  2 -> 3 ($50)" << endl;
            cout << "  2 -> 4 ($100)" << endl;
            cout << "  3 -> 4 ($60)" << endl;
            
            vector<vector<int>> flights = {
                {0, 1, 50}, {0, 2, 200}, {1, 2, 40}, 
                {1, 3, 70}, {2, 3, 50}, {2, 4, 100}, {3, 4, 60}
            };
            solver.findCheapestPath(5, flights, 0, 4);
        }
        else if(choice == 3) {
            int n, m, src, dst;
            cout << "Enter number of cities: ";
            cin >> n;
            cout << "Enter number of flights: ";
            cin >> m;
            cout << "Enter source city: ";
            cin >> src;
            cout << "Enter destination city: ";
            cin >> dst;
            
            vector<vector<int>> flights;
            cout << "Enter flights (from to price):" << endl;
            for(int i = 0; i < m; i++) {
                int from, to, price;
                cout << "Flight " << (i+1) << ": ";
                cin >> from >> to >> price;
                flights.push_back({from, to, price});
            }
            
            solver.findCheapestPath(n, flights, src, dst);
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
