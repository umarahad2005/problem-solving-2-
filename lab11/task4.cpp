// Lab 11 Task 4: Count total number of edges using adjacency list
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

    int countEdges() {
        int totalDegree = 0;
        
        // Sum up all the sizes of adjacency lists
        for(int i = 0; i < numVertices; i++) {
            totalDegree += adjList[i].size();
        }
        
        // For undirected graph, each edge is counted twice
        // So divide by 2 to get actual number of edges
        return totalDegree / 2;
    }

    void display() {
        cout << "\nAdjacency List:" << endl;
        for(int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << ":";
            for(int j = 0; j < adjList[i].size(); j++) {
                cout << " -> " << adjList[i][j];
            }
            cout << " (degree: " << adjList[i].size() << ")" << endl;
        }
    }
};

int main() {
    cout << "Task 4: Count Total Number of Edges in Graph" << endl;
    cout << "=============================================" << endl;
    
    Graph g(5);
    
    // Adding edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    
    g.display();
    
    cout << "\nTotal number of edges in the graph: " << g.countEdges() << endl;
    
    // Another example with different graph
    cout << "\n\n--- Another Example ---" << endl;
    
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(0, 3);
    g2.addEdge(1, 2);
    
    g2.display();
    cout << "\nTotal number of edges in graph 2: " << g2.countEdges() << endl;
    
    return 0;
}
