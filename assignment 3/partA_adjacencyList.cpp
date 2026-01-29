/*
 * Assignment 3 - Part A: Directed Graph using Adjacency List
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
#include <list>
#include <string>
#include <iomanip>
#include <unordered_map>
using namespace std;

// Structure to represent an edge (for weighted graphs)
struct Edge {
    int destination;
    int weight;

    Edge(int dest, int w = 1) : destination(dest), weight(w) {}
};

class DirectedGraphList {
private:
    vector<list<Edge>> adjList;
    vector<string> vertexNames;
    unordered_map<string, int> nameToIndex;
    int vertexCount;

public:
    DirectedGraphList() : vertexCount(0) {}

    // Insert a new vertex
    bool insertVertex(const string& name) {
        // Check if vertex already exists
        if (nameToIndex.find(name) != nameToIndex.end()) {
            cout << "Vertex '" << name << "' already exists!" << endl;
            return false;
        }

        nameToIndex[name] = vertexCount;
        vertexNames.push_back(name);
        adjList.push_back(list<Edge>());
        vertexCount++;

        cout << "Vertex '" << name << "' added successfully. (Index: " << vertexCount - 1 << ")" << endl;
        return true;
    }

    // Insert a directed edge from source to destination
    bool insertEdge(const string& source, const string& destination, int weight = 1) {
        // Check if vertices exist
        if (nameToIndex.find(source) == nameToIndex.end()) {
            cout << "Source vertex '" << source << "' not found!" << endl;
            return false;
        }

        if (nameToIndex.find(destination) == nameToIndex.end()) {
            cout << "Destination vertex '" << destination << "' not found!" << endl;
            return false;
        }

        int srcIndex = nameToIndex[source];
        int destIndex = nameToIndex[destination];

        // Check if edge already exists
        for (const Edge& e : adjList[srcIndex]) {
            if (e.destination == destIndex) {
                cout << "Edge from '" << source << "' to '" << destination << "' already exists!" << endl;
                return false;
            }
        }

        adjList[srcIndex].push_back(Edge(destIndex, weight));
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

        adjList[srcIndex].push_back(Edge(destIndex, weight));
        cout << "Edge added: " << vertexNames[srcIndex] << " -> " << vertexNames[destIndex] << endl;
        return true;
    }

    // Remove an edge
    bool removeEdge(const string& source, const string& destination) {
        if (nameToIndex.find(source) == nameToIndex.end() || 
            nameToIndex.find(destination) == nameToIndex.end()) {
            cout << "Vertex not found!" << endl;
            return false;
        }

        int srcIndex = nameToIndex[source];
        int destIndex = nameToIndex[destination];

        for (auto it = adjList[srcIndex].begin(); it != adjList[srcIndex].end(); ++it) {
            if (it->destination == destIndex) {
                adjList[srcIndex].erase(it);
                cout << "Edge removed: " << source << " -> " << destination << endl;
                return true;
            }
        }

        cout << "Edge does not exist!" << endl;
        return false;
    }

    // Display the adjacency list
    void displayList() {
        if (vertexCount == 0) {
            cout << "Graph is empty!" << endl;
            return;
        }

        cout << "\n========== ADJACENCY LIST ==========" << endl;
        cout << "Number of vertices: " << vertexCount << endl;
        cout << "\nList representation:" << endl;

        for (int i = 0; i < vertexCount; i++) {
            cout << setw(8) << vertexNames[i] << " -> ";

            if (adjList[i].empty()) {
                cout << "(no outgoing edges)";
            } else {
                bool first = true;
                for (const Edge& e : adjList[i]) {
                    if (!first) cout << " -> ";
                    cout << vertexNames[e.destination];
                    if (e.weight != 1) cout << "(" << e.weight << ")";
                    first = false;
                }
            }
            cout << endl;
        }
        cout << "=====================================" << endl;
    }

    // Display the graph
    void displayGraph() {
        if (vertexCount == 0) {
            cout << "Graph is empty!" << endl;
            return;
        }

        cout << "\n========== DIRECTED GRAPH (Adjacency List) ==========" << endl;
        cout << "Vertices: ";
        for (int i = 0; i < vertexCount; i++) {
            cout << vertexNames[i];
            if (i < vertexCount - 1) cout << ", ";
        }
        cout << endl;

        cout << "\nEdges (Source -> Destination):" << endl;
        int edgeNum = 1;
        for (int i = 0; i < vertexCount; i++) {
            for (const Edge& e : adjList[i]) {
                cout << "  " << edgeNum++ << ". " << vertexNames[i] << " -> " << vertexNames[e.destination];
                if (e.weight != 1) {
                    cout << " (weight: " << e.weight << ")";
                }
                cout << endl;
            }
        }

        if (edgeNum == 1) {
            cout << "  No edges in the graph." << endl;
        }
        cout << "=====================================================" << endl;
    }

    // Count total number of edges
    int countEdges() {
        int count = 0;
        for (int i = 0; i < vertexCount; i++) {
            count += adjList[i].size();
        }
        return count;
    }

    // Get in-degree of a vertex
    int getInDegree(const string& vertex) {
        if (nameToIndex.find(vertex) == nameToIndex.end()) return -1;
        int index = nameToIndex[vertex];

        int inDegree = 0;
        for (int i = 0; i < vertexCount; i++) {
            for (const Edge& e : adjList[i]) {
                if (e.destination == index) {
                    inDegree++;
                }
            }
        }
        return inDegree;
    }

    // Get out-degree of a vertex
    int getOutDegree(const string& vertex) {
        if (nameToIndex.find(vertex) == nameToIndex.end()) return -1;
        int index = nameToIndex[vertex];
        return adjList[index].size();
    }

    // Check if edge exists
    bool hasEdge(const string& source, const string& destination) {
        if (nameToIndex.find(source) == nameToIndex.end() || 
            nameToIndex.find(destination) == nameToIndex.end()) {
            return false;
        }

        int srcIndex = nameToIndex[source];
        int destIndex = nameToIndex[destination];

        for (const Edge& e : adjList[srcIndex]) {
            if (e.destination == destIndex) {
                return true;
            }
        }
        return false;
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

    // Get neighbors of a vertex
    vector<string> getNeighbors(const string& vertex) {
        vector<string> neighbors;
        if (nameToIndex.find(vertex) == nameToIndex.end()) return neighbors;

        int index = nameToIndex[vertex];
        for (const Edge& e : adjList[index]) {
            neighbors.push_back(vertexNames[e.destination]);
        }
        return neighbors;
    }
};

int main() {
    cout << "=============================================" << endl;
    cout << "  Assignment 3 - Part A: Adjacency List" << endl;
    cout << "  Directed Graph Implementation" << endl;
    cout << "=============================================" << endl;

    DirectedGraphList graph;

    // Insert vertices (same as adjacency matrix example for comparison)
    cout << "\n--- Inserting Vertices ---" << endl;
    graph.insertVertex("A");
    graph.insertVertex("B");
    graph.insertVertex("C");
    graph.insertVertex("D");
    graph.insertVertex("E");

    // Insert edges (directed) - same edges as matrix example
    cout << "\n--- Inserting Edges ---" << endl;
    graph.insertEdge("A", "B");
    graph.insertEdge("A", "C");
    graph.insertEdge("B", "C");
    graph.insertEdge("B", "D");
    graph.insertEdge("C", "D");
    graph.insertEdge("D", "E");
    graph.insertEdge("E", "A");  // Creates a cycle

    // Display the adjacency list
    graph.displayList();

    // Display the graph
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

    // Display neighbors
    cout << "\n--- Neighbors (Outgoing Connections) ---" << endl;
    for (const string& v : {"A", "B", "C", "D", "E"}) {
        cout << v << ": ";
        vector<string> neighbors = graph.getNeighbors(v);
        if (neighbors.empty()) {
            cout << "(none)";
        } else {
            for (size_t i = 0; i < neighbors.size(); i++) {
                cout << neighbors[i];
                if (i < neighbors.size() - 1) cout << ", ";
            }
        }
        cout << endl;
    }

    // Demonstrate removing an edge
    cout << "\n--- Removing Edge ---" << endl;
    graph.removeEdge("E", "A");
    cout << "\nAfter removing edge E -> A:" << endl;
    cout << "Total number of edges: " << graph.countEdges() << endl;
    graph.displayList();

    return 0;
}
