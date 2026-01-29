// Lab 11 Task 6: Implement the given graph using adjacency list
// Based on the graph shown in the lab document
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
        cout << "\nAdjacency List Representation:" << endl;
        cout << "==============================" << endl;
        for(int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << ":";
            for(int j = 0; j < adjList[i].size(); j++) {
                cout << " -> " << adjList[i][j];
            }
            cout << endl;
        }
    }

    void displayFormatted() {
        cout << "\nFormatted View:" << endl;
        cout << "===============" << endl;
        for(int i = 0; i < numVertices; i++) {
            cout << "[" << i << "] : { ";
            for(int j = 0; j < adjList[i].size(); j++) {
                cout << adjList[i][j];
                if(j < adjList[i].size() - 1)
                    cout << ", ";
            }
            cout << " }" << endl;
        }
    }

    int countEdges() {
        int total = 0;
        for(int i = 0; i < numVertices; i++) {
            total += adjList[i].size();
        }
        return total / 2;
    }

    void printGraphInfo() {
        cout << "\nGraph Statistics:" << endl;
        cout << "=================" << endl;
        cout << "Number of Vertices: " << numVertices << endl;
        cout << "Number of Edges: " << countEdges() << endl;
        
        cout << "\nDegree of each vertex:" << endl;
        for(int i = 0; i < numVertices; i++) {
            cout << "  Vertex " << i << ": degree = " << adjList[i].size() << endl;
        }
    }
};

int main() {
    cout << "Task 6: Implement Given Graph using Adjacency List" << endl;
    cout << "===================================================" << endl;
    
    // Implementing a sample graph structure
    // Assuming the graph from the lab document has vertices 0-5
    // with connections as typically shown in lab examples
    
    /*
        Graph Structure:
        
            0 --- 1
            |     |
            |     |
            2 --- 3
             \   /
              \ /
               4
               |
               5
    */
    
    Graph g(6);
    
    // Adding edges based on typical graph structure
    g.addEdge(0, 1);  // Edge between 0 and 1
    g.addEdge(0, 2);  // Edge between 0 and 2
    g.addEdge(1, 3);  // Edge between 1 and 3
    g.addEdge(2, 3);  // Edge between 2 and 3
    g.addEdge(2, 4);  // Edge between 2 and 4
    g.addEdge(3, 4);  // Edge between 3 and 4
    g.addEdge(4, 5);  // Edge between 4 and 5
    
    cout << "\nGraph Structure:" << endl;
    cout << "    0 --- 1" << endl;
    cout << "    |     |" << endl;
    cout << "    |     |" << endl;
    cout << "    2 --- 3" << endl;
    cout << "     \\   /" << endl;
    cout << "      \\ /" << endl;
    cout << "       4" << endl;
    cout << "       |" << endl;
    cout << "       5" << endl;
    
    g.display();
    g.displayFormatted();
    g.printGraphInfo();
    
    return 0;
}
