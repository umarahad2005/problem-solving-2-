// Lab 11 Task 3: Implement and print adjacency list of an undirected graph
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

    void printGraph() {
        cout << "\nAdjacency List Representation of Undirected Graph:" << endl;
        cout << "===================================================" << endl;
        for(int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i;
            for(int j = 0; j < adjList[i].size(); j++) {
                cout << " --> " << adjList[i][j];
            }
            cout << endl;
        }
    }

    void printGraphFormatted() {
        cout << "\nFormatted Adjacency List:" << endl;
        cout << "=========================" << endl;
        for(int i = 0; i < numVertices; i++) {
            cout << "[" << i << "] : ";
            for(int j = 0; j < adjList[i].size(); j++) {
                cout << adjList[i][j];
                if(j < adjList[i].size() - 1)
                    cout << ", ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "Task 3: Adjacency List of an Undirected Graph" << endl;
    cout << "==============================================" << endl;
    
    int vertices, edges;
    cout << "\nEnter number of vertices: ";
    cin >> vertices;
    
    Graph g(vertices);
    
    cout << "Enter number of edges: ";
    cin >> edges;
    
    cout << "\nEnter edges (source destination):" << endl;
    for(int i = 0; i < edges; i++) {
        int src, dest;
        cout << "Edge " << i + 1 << ": ";
        cin >> src >> dest;
        g.addEdge(src, dest);
    }
    
    g.printGraph();
    g.printGraphFormatted();
    
    return 0;
}
