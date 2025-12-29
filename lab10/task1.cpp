#include<iostream>
using namespace std;

class Graph {
private:
    int numVertices;
    int adj[10][10];

public:
    Graph(int vertices) {
        numVertices = vertices;
        for(int i = 0; i < numVertices; i++) {
            for(int j = 0; j < numVertices; j++) {
                adj[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1; 
    }

    void display() {
        cout << "  ";
        for(int i = 0; i < numVertices; i++) {
            cout << i << " ";
        }
        cout << endl;
        
        for(int i = 0; i < numVertices; i++) {
            cout << i << " ";
            for(int j = 0; j < numVertices; j++) {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "Task 1: Adjacency Matrix for graph with 5 vertices and 4 edges" << endl;
    cout << "================================================================" << endl;
    
    Graph g(5);
    
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    
    cout << "\nAdjacency Matrix:" << endl;
    g.display();
    
    return 0;
}