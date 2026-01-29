// Lab 11 Task 2: Check if edge exists between two vertices in adjacency list
#include<iostream>
#include<vector>
using namespace std;

class Graph {
private:
    int numVertices;
    vector<int> adjList[10];

public:
    Graph(int vertices) {
        numVertices = vertices;
    }

    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src); // For undirected graph
    }

    bool hasEdge(int u, int v) {
        // Search for v in the adjacency list of u
        for(int i = 0; i < adjList[u].size(); i++) {
            if(adjList[u][i] == v) {
                return true;
            }
        }
        return false;
    }

    void display() {
        cout << "\nAdjacency List:" << endl;
        for(int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << ":";
            for(int j = 0; j < adjList[i].size(); j++) {
                cout << " -> " << adjList[i][j];
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "Task 2: Check if edge exists between two vertices" << endl;
    cout << "==================================================" << endl;
    
    Graph g(5);
    
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    
    g.display();
    
    cout << "\nEdge Checks:" << endl;
    cout << "------------" << endl;
    
    // Check if edge exists between 0 and 1
    if(g.hasEdge(0, 1))
        cout << "Edge exists between vertex 0 and vertex 1" << endl;
    else
        cout << "No edge between vertex 0 and vertex 1" << endl;
    
    // Check if edge exists between 0 and 2
    if(g.hasEdge(0, 2))
        cout << "Edge exists between vertex 0 and vertex 2" << endl;
    else
        cout << "No edge between vertex 0 and vertex 2" << endl;
    
    // Check if edge exists between 2 and 3
    if(g.hasEdge(2, 3))
        cout << "Edge exists between vertex 2 and vertex 3" << endl;
    else
        cout << "No edge between vertex 2 and vertex 3" << endl;
    
    // Check if edge exists between 1 and 4
    if(g.hasEdge(1, 4))
        cout << "Edge exists between vertex 1 and vertex 4" << endl;
    else
        cout << "No edge between vertex 1 and vertex 4" << endl;
    
    return 0;
}
