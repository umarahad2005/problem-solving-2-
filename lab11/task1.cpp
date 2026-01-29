// Lab 11 Task 1: Create an adjacency List for a graph with 5 vertices and 4 edges
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
    cout << "Task 1: Adjacency List for graph with 5 vertices and 4 edges" << endl;
    cout << "============================================================" << endl;
    
    Graph g(5);
    
    // Adding 4 edges
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    
    g.display();
    
    return 0;
}
