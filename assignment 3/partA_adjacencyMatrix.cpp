/*
 * Assignment 3 - Part A: Directed Graph using Adjacency Matrix
 * Course: Problem Solving II (CS4703)
 * Riphah International University - BSCS 4th Semester
 * 
 * Operations:
 * - Insertion of vertices and edges
 * - Display the graph
 * - Count total number of edges
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class DirectedGraphMatrix {
private:
    vector<vector<int>> adjMatrix;
    vector<string> vertexNames;
    int vertexCount;
    int maxVertices;

    // Find index of vertex by name
    int getVertexIndex(const string& name) {
        for (int i = 0; i < vertexCount; i++) {
            if (vertexNames[i] == name) {
                return i;
            }
        }
        return -1;
    }

public:
    // Constructor with maximum vertices capacity
    DirectedGraphMatrix(int maxV = 10) : maxVertices(maxV), vertexCount(0) {
        adjMatrix.resize(maxVertices, vector<int>(maxVertices, 0));
        vertexNames.resize(maxVertices);
    }

    // Insert a new vertex
    bool insertVertex(const string& name) {
        // Check if vertex already exists
        if (getVertexIndex(name) != -1) {
            cout << "Vertex '" << name << "' already exists!" << endl;
            return false;
        }

        // Check if we have space
        if (vertexCount >= maxVertices) {
            cout << "Graph is full! Cannot add more vertices." << endl;
            return false;
        }

        vertexNames[vertexCount] = name;
        vertexCount++;
        cout << "Vertex '" << name << "' added successfully. (Index: " << vertexCount - 1 << ")" << endl;
        return true;
    }

    // Insert a directed edge from source to destination
    bool insertEdge(const string& source, const string& destination, int weight = 1) {
        int srcIndex = getVertexIndex(source);
        int destIndex = getVertexIndex(destination);

        if (srcIndex == -1) {
            cout << "Source vertex '" << source << "' not found!" << endl;
            return false;
        }

        if (destIndex == -1) {
            cout << "Destination vertex '" << destination << "' not found!" << endl;
            return false;
        }

        if (adjMatrix[srcIndex][destIndex] != 0) {
            cout << "Edge from '" << source << "' to '" << destination << "' already exists!" << endl;
            return false;
        }

        adjMatrix[srcIndex][destIndex] = weight;
        cout << "Edge added: " << source << " -> " << destination;
        if (weight != 1) cout << " (weight: " << weight << ")";
        cout << endl;
        return true;
    }

    // Insert edge using vertex indices
    bool insertEdgeByIndex(int srcIndex, int destIndex, int weight = 1) {
        if (srcIndex < 0 || srcIndex >= vertexCount || destIndex < 0 || destIndex >= vertexCount) {
            cout << "Invalid vertex index!" << endl;
            return false;
        }

        adjMatrix[srcIndex][destIndex] = weight;
        cout << "Edge added: " << vertexNames[srcIndex] << " -> " << vertexNames[destIndex] << endl;
        return true;
    }

    // Remove an edge
    bool removeEdge(const string& source, const string& destination) {
        int srcIndex = getVertexIndex(source);
        int destIndex = getVertexIndex(destination);

        if (srcIndex == -1 || destIndex == -1) {
            cout << "Vertex not found!" << endl;
            return false;
        }

        if (adjMatrix[srcIndex][destIndex] == 0) {
            cout << "Edge does not exist!" << endl;
            return false;
        }

        adjMatrix[srcIndex][destIndex] = 0;
        cout << "Edge removed: " << source << " -> " << destination << endl;
        return true;
    }

    // Display the adjacency matrix
    void displayMatrix() {
        if (vertexCount == 0) {
            cout << "Graph is empty!" << endl;
            return;
        }

        cout << "\n========== ADJACENCY MATRIX ==========" << endl;
        cout << "Number of vertices: " << vertexCount << endl;
        cout << "\nMatrix representation:" << endl;

        // Print header row
        cout << setw(12) << " ";
        for (int i = 0; i < vertexCount; i++) {
            cout << setw(8) << vertexNames[i];
        }
        cout << endl;

        // Print separator
        cout << setw(12) << " ";
        for (int i = 0; i < vertexCount; i++) {
            cout << "--------";
        }
        cout << endl;

        // Print matrix rows
        for (int i = 0; i < vertexCount; i++) {
            cout << setw(10) << vertexNames[i] << " |";
            for (int j = 0; j < vertexCount; j++) {
                cout << setw(8) << adjMatrix[i][j];
            }
            cout << endl;
        }
        cout << "=======================================" << endl;
    }

    // Display the graph as edge list
    void displayGraph() {
        if (vertexCount == 0) {
            cout << "Graph is empty!" << endl;
            return;
        }

        cout << "\n========== DIRECTED GRAPH (Adjacency Matrix) ==========" << endl;
        cout << "Vertices: ";
        for (int i = 0; i < vertexCount; i++) {
            cout << vertexNames[i];
            if (i < vertexCount - 1) cout << ", ";
        }
        cout << endl;

        cout << "\nEdges (Source -> Destination):" << endl;
        int edgeNum = 1;
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                if (adjMatrix[i][j] != 0) {
                    cout << "  " << edgeNum++ << ". " << vertexNames[i] << " -> " << vertexNames[j];
                    if (adjMatrix[i][j] != 1) {
                        cout << " (weight: " << adjMatrix[i][j] << ")";
                    }
                    cout << endl;
                }
            }
        }

        if (edgeNum == 1) {
            cout << "  No edges in the graph." << endl;
        }
        cout << "=======================================================" << endl;
    }

    // Count total number of edges
    int countEdges() {
        int count = 0;
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                if (adjMatrix[i][j] != 0) {
                    count++;
                }
            }
        }
        return count;
    }

    // Get in-degree of a vertex
    int getInDegree(const string& vertex) {
        int index = getVertexIndex(vertex);
        if (index == -1) return -1;

        int inDegree = 0;
        for (int i = 0; i < vertexCount; i++) {
            if (adjMatrix[i][index] != 0) {
                inDegree++;
            }
        }
        return inDegree;
    }

    // Get out-degree of a vertex
    int getOutDegree(const string& vertex) {
        int index = getVertexIndex(vertex);
        if (index == -1) return -1;

        int outDegree = 0;
        for (int j = 0; j < vertexCount; j++) {
            if (adjMatrix[index][j] != 0) {
                outDegree++;
            }
        }
        return outDegree;
    }

    // Check if edge exists
    bool hasEdge(const string& source, const string& destination) {
        int srcIndex = getVertexIndex(source);
        int destIndex = getVertexIndex(destination);

        if (srcIndex == -1 || destIndex == -1) return false;
        return adjMatrix[srcIndex][destIndex] != 0;
    }

    // Get number of vertices
    int getVertexCount() {
        return vertexCount;
    }

    // Display vertex degrees
    void displayDegrees() {
        cout << "\n========== VERTEX DEGREES ==========" << endl;
        cout << setw(12) << "Vertex" << setw(12) << "In-Degree" << setw(12) << "Out-Degree" << endl;
        cout << "------------------------------------" << endl;

        for (int i = 0; i < vertexCount; i++) {
            cout << setw(12) << vertexNames[i] 
                 << setw(12) << getInDegree(vertexNames[i])
                 << setw(12) << getOutDegree(vertexNames[i]) << endl;
        }
        cout << "=====================================" << endl;
    }
};

int main() {
    cout << "=============================================" << endl;
    cout << "  Assignment 3 - Part A: Adjacency Matrix" << endl;
    cout << "  Directed Graph Implementation" << endl;
    cout << "=============================================" << endl;

    DirectedGraphMatrix graph(10);

    // Insert vertices
    cout << "\n--- Inserting Vertices ---" << endl;
    graph.insertVertex("A");
    graph.insertVertex("B");
    graph.insertVertex("C");
    graph.insertVertex("D");
    graph.insertVertex("E");

    // Insert edges (directed)
    cout << "\n--- Inserting Edges ---" << endl;
    graph.insertEdge("A", "B");
    graph.insertEdge("A", "C");
    graph.insertEdge("B", "C");
    graph.insertEdge("B", "D");
    graph.insertEdge("C", "D");
    graph.insertEdge("D", "E");
    graph.insertEdge("E", "A");  // Creates a cycle

    // Display the adjacency matrix
    graph.displayMatrix();

    // Display the graph as edge list
    graph.displayGraph();

    // Count and display total edges
    cout << "\n--- Edge Count ---" << endl;
    cout << "Total number of edges: " << graph.countEdges() << endl;

    // Display vertex degrees
    graph.displayDegrees();

    // Test edge existence
    cout << "\n--- Edge Existence Check ---" << endl;
    cout << "Edge A -> B exists: " << (graph.hasEdge("A", "B") ? "Yes" : "No") << endl;
    cout << "Edge B -> A exists: " << (graph.hasEdge("B", "A") ? "Yes" : "No") << endl;
    cout << "Edge C -> D exists: " << (graph.hasEdge("C", "D") ? "Yes" : "No") << endl;

    // Demonstrate removing an edge
    cout << "\n--- Removing Edge ---" << endl;
    graph.removeEdge("E", "A");
    cout << "\nAfter removing edge E -> A:" << endl;
    cout << "Total number of edges: " << graph.countEdges() << endl;
    graph.displayMatrix();

    return 0;
}
