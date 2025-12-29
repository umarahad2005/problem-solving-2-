// Task 2: Check if edge exists between two vertices
#include<iostream>
using namespace std;

class Graph {
    int adj[10][10];
    int n;

public:
    Graph(int vertices) {
        n = vertices;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                adj[i][j] = 0;
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    bool hasEdge(int u, int v) {
        return adj[u][v] == 1;
    }
};

int main() {
    Graph g(5);
    
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    
    // Check if edge exists
    if(g.hasEdge(0, 1))
        cout << "Edge exists between 0 and 1" << endl;
    else
        cout << "No edge between 0 and 1" << endl;

    if(g.hasEdge(0, 2))
        cout << "Edge exists between 0 and 2" << endl;
    else
        cout << "No edge between 0 and 2" << endl;
    
    return 0;
}
