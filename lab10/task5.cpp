

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

    int countEdges() {
        int count = 0;
        for(int i = 0; i < numVertices; i++) {
            for(int j = i + 1; j < numVertices; j++) { 
                if(adj[i][j] == 1) {
                    count++;
                }
            }
        }
        return count;
    }
};

int main() {
    cout << "Task 5: Implementing the given graph using Adjacency Matrix" << endl;
    cout << "============================================================" << endl;
    
    
    Graph g(6);
    
    g.addEdge(1, 2);  
    g.addEdge(1, 5);  
    g.addEdge(1, 4);  
    g.addEdge(2, 3);  
    g.addEdge(2, 5);  
    g.addEdge(3, 5);            
    g.addEdge(3, 0);  
    g.addEdge(4, 5);  
    g.addEdge(4, 0);  
    g.addEdge(5, 0);  
    
    cout << "\nAdjacency Matrix Representation:" << endl;
    g.display();
    
    cout << "\nTotal number of edges: " << g.countEdges() << endl;
    
    
    return 0;
}
