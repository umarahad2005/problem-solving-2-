// Lab 11 Task 5: Server Network - Remove connection and analyze adjacency list
// S1=0, S2=1, S3=2, S4=3 in a fully connected mesh (each server connected to every other)
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
        adjList[dest].push_back(src);
    }

    void removeEdge(int src, int dest) {
        // Remove dest from src's list
        for(int i = 0; i < adjList[src].size(); i++) {
            if(adjList[src][i] == dest) {
                adjList[src].erase(adjList[src].begin() + i);
                break;
            }
        }
        // Remove src from dest's list
        for(int i = 0; i < adjList[dest].size(); i++) {
            if(adjList[dest][i] == src) {
                adjList[dest].erase(adjList[dest].begin() + i);
                break;
            }
        }
    }

    int countTotalConnections() {
        int total = 0;
        for(int i = 0; i < numVertices; i++) {
            total += adjList[i].size();
        }
        return total;
    }

    void display() {
        cout << "\nAdjacency List:" << endl;
        for(int i = 0; i < numVertices; i++) {
            cout << "S" << i + 1 << " (Vertex " << i << "):";
            for(int j = 0; j < adjList[i].size(); j++) {
                cout << " -> S" << adjList[i][j] + 1;
            }
            cout << endl;
        }
    }

    // Convert to matrix for comparison
    void printAsMatrix() {
        int matrix[10][10] = {0};
        for(int i = 0; i < numVertices; i++) {
            for(int j = 0; j < adjList[i].size(); j++) {
                matrix[i][adjList[i][j]] = 1;
            }
        }
        
        cout << "\nEquivalent Adjacency Matrix:" << endl;
        cout << "    ";
        for(int i = 0; i < numVertices; i++) {
            cout << "S" << i + 1 << " ";
        }
        cout << endl;
        
        for(int i = 0; i < numVertices; i++) {
            cout << "S" << i + 1 << "  ";
            for(int j = 0; j < numVertices; j++) {
                cout << matrix[i][j] << "  ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "Task 5: Server Network Analysis with Adjacency List" << endl;
    cout << "====================================================" << endl;
    cout << "Servers: S1=0, S2=1, S3=2, S4=3" << endl;
    
    Graph g(4);
    
    // Create fully connected mesh - each server connected to every other
    g.addEdge(0, 1);  // S1-S2
    g.addEdge(0, 2);  // S1-S3
    g.addEdge(0, 3);  // S1-S4
    g.addEdge(1, 2);  // S2-S3
    g.addEdge(1, 3);  // S2-S4
    g.addEdge(2, 3);  // S3-S4
    
    cout << "\n=== BEFORE removing connection between S2 and S3 ===" << endl;
    g.display();
    g.printAsMatrix();
    
    int beforeConnections = g.countTotalConnections();
    cout << "\nTotal entries (1's) in adjacency representation: " << beforeConnections << endl;
    
    // Remove connection between S2 (1) and S3 (2)
    cout << "\n*** Removing cable connection between S2 and S3 ***" << endl;
    g.removeEdge(1, 2);
    
    cout << "\n=== AFTER removing connection between S2 and S3 ===" << endl;
    g.display();
    g.printAsMatrix();
    
    int afterConnections = g.countTotalConnections();
    
    cout << "\n========================================" << endl;
    cout << "ANSWERS TO THE QUESTIONS:" << endl;
    cout << "========================================" << endl;
    
    cout << "\n1. How many 1's will remain in the entire adjacency list/matrix?" << endl;
    cout << "   Answer: " << afterConnections << " entries remain" << endl;
    cout << "   (Before: " << beforeConnections << ", After: " << afterConnections << ")" << endl;
    
    cout << "\n2. What specific matrix positions ([i][j] pairs) will change from 1 to 0?" << endl;
    cout << "   Answer: [1][2] and [2][1] (i.e., S2-S3 connection in both directions)" << endl;
    
    cout << "\n3. Will the matrix remain symmetric? Why or why not?" << endl;
    cout << "   Answer: YES, the matrix will remain symmetric." << endl;
    cout << "   Reason: When we remove an edge in an undirected graph, we remove" << endl;
    cout << "   both [i][j] and [j][i] entries. Since the original matrix was" << endl;
    cout << "   symmetric (undirected graph) and we removed both symmetric" << endl;
    cout << "   positions, the resulting matrix remains symmetric." << endl;
    
    return 0;
}
