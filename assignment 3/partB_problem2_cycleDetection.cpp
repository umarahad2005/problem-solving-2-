/*
 * Assignment 3 - Part B: Problem 2 - Cycle Detection in Graph
 * Course: Problem Solving II (CS4703)
 * Riphah International University - BSCS 4th Semester
 * 
 * Problem Statement:
 * Detect whether a directed graph contains a cycle. A cycle exists when
 * you can start from a vertex and follow edges to return to the same vertex.
 * 
 * Graph Type: Directed Graph using Adjacency List
 * 
 * Logic:
 * We use DFS with coloring technique:
 * - WHITE (0): Vertex not yet visited
 * - GRAY (1): Vertex is being processed (in current DFS path)
 * - BLACK (2): Vertex and all its descendants are fully processed
 * 
 * A cycle exists if we encounter a GRAY vertex during DFS
 * (meaning we've found a back edge to an ancestor in current path)
 * 
 * Applications:
 * - Deadlock detection in operating systems
 * - Dependency resolution (detecting circular dependencies)
 * - Course prerequisite validation
 */

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
using namespace std;

// Color states for DFS
enum Color { WHITE, GRAY, BLACK };

class DirectedGraph {
private:
    vector<list<int>> adjList;
    vector<string> vertexNames;
    unordered_map<string, int> nameToIndex;
    int vertexCount;

public:
    DirectedGraph() : vertexCount(0) {}

    void addVertex(const string& name) {
        if (nameToIndex.find(name) != nameToIndex.end()) return;
        nameToIndex[name] = vertexCount;
        vertexNames.push_back(name);
        adjList.push_back(list<int>());
        vertexCount++;
    }

    void addEdge(const string& source, const string& destination) {
        if (nameToIndex.find(source) == nameToIndex.end() ||
            nameToIndex.find(destination) == nameToIndex.end()) {
            cout << "Vertex not found!" << endl;
            return;
        }
        int srcIdx = nameToIndex[source];
        int destIdx = nameToIndex[destination];
        adjList[srcIdx].push_back(destIdx);
    }

    void displayGraph() {
        cout << "\n========== GRAPH STRUCTURE ==========" << endl;
        for (int i = 0; i < vertexCount; i++) {
            cout << vertexNames[i] << " -> ";
            bool first = true;
            for (int neighbor : adjList[i]) {
                if (!first) cout << ", ";
                cout << vertexNames[neighbor];
                first = false;
            }
            if (adjList[i].empty()) cout << "(no edges)";
            cout << endl;
        }
        cout << "======================================" << endl;
    }

    /*
     * CYCLE DETECTION USING DFS WITH COLORS
     * 
     * Algorithm:
     * 1. Initialize all vertices as WHITE (unvisited)
     * 2. For each unvisited vertex, start DFS
     * 3. When visiting a vertex:
     *    a. Mark it GRAY (in progress)
     *    b. Visit all neighbors
     *    c. If neighbor is GRAY -> CYCLE FOUND (back edge)
     *    d. If neighbor is WHITE -> recursively visit
     *    e. After all neighbors processed, mark BLACK
     * 
     * Time Complexity: O(V + E)
     * Space Complexity: O(V) for color array and recursion stack
     */
    bool detectCycle() {
        cout << "\n========== CYCLE DETECTION ==========" << endl;
        cout << "Using DFS with coloring technique" << endl;
        cout << "Colors: WHITE=unvisited, GRAY=in-progress, BLACK=done" << endl;
        cout << "--------------------------------------" << endl;

        vector<Color> color(vertexCount, WHITE);
        vector<int> cyclePath;
        bool hasCycle = false;
        int cycleStart = -1;

        for (int i = 0; i < vertexCount; i++) {
            if (color[i] == WHITE) {
                cout << "\nStarting DFS from vertex: " << vertexNames[i] << endl;
                if (detectCycleUtil(i, color, cyclePath, cycleStart)) {
                    hasCycle = true;
                    break;
                }
            }
        }

        cout << "--------------------------------------" << endl;
        if (hasCycle) {
            cout << "\n*** CYCLE DETECTED! ***" << endl;
            cout << "Cycle path: ";
            
            // Find and print the cycle
            bool inCycle = false;
            for (int v : cyclePath) {
                if (v == cycleStart) inCycle = true;
                if (inCycle) {
                    cout << vertexNames[v];
                    if (v != cyclePath.back()) cout << " -> ";
                }
            }
            cout << " -> " << vertexNames[cycleStart] << " (back to start)" << endl;
        } else {
            cout << "\nNo cycle detected. Graph is acyclic (DAG)." << endl;
        }
        cout << "======================================" << endl;

        return hasCycle;
    }

private:
    bool detectCycleUtil(int vertex, vector<Color>& color, 
                         vector<int>& path, int& cycleStart) {
        // Mark current vertex as being processed
        color[vertex] = GRAY;
        path.push_back(vertex);
        cout << "  Visiting " << vertexNames[vertex] << " (GRAY)" << endl;

        // Visit all neighbors
        for (int neighbor : adjList[vertex]) {
            cout << "    Checking edge: " << vertexNames[vertex] 
                 << " -> " << vertexNames[neighbor];

            if (color[neighbor] == GRAY) {
                // Back edge found - cycle detected!
                cout << " [BACK EDGE - CYCLE!]" << endl;
                cycleStart = neighbor;
                path.push_back(neighbor);
                return true;
            }
            
            if (color[neighbor] == WHITE) {
                cout << " [Tree edge - exploring]" << endl;
                if (detectCycleUtil(neighbor, color, path, cycleStart)) {
                    return true;
                }
            } else {
                cout << " [Forward/Cross edge - skip]" << endl;
            }
        }

        // Mark vertex as fully processed
        color[vertex] = BLACK;
        path.pop_back();
        cout << "  Finished " << vertexNames[vertex] << " (BLACK)" << endl;
        return false;
    }

public:
    /*
     * DETECT ALL CYCLES (Finding all cycles in the graph)
     * Uses a modified DFS to find all back edges
     */
    void findAllCycles() {
        cout << "\n========== FIND ALL BACK EDGES ==========" << endl;

        vector<Color> color(vertexCount, WHITE);
        vector<int> parent(vertexCount, -1);
        int backEdgeCount = 0;

        for (int i = 0; i < vertexCount; i++) {
            if (color[i] == WHITE) {
                findAllCyclesUtil(i, color, parent, backEdgeCount);
            }
        }

        cout << "\nTotal back edges (cycles): " << backEdgeCount << endl;
        cout << "===========================================" << endl;
    }

private:
    void findAllCyclesUtil(int vertex, vector<Color>& color, 
                          vector<int>& parent, int& backEdgeCount) {
        color[vertex] = GRAY;

        for (int neighbor : adjList[vertex]) {
            if (color[neighbor] == GRAY) {
                // Back edge found
                backEdgeCount++;
                cout << "Back edge " << backEdgeCount << ": " 
                     << vertexNames[vertex] << " -> " << vertexNames[neighbor] << endl;
                
                // Print the cycle
                cout << "  Cycle: " << vertexNames[neighbor];
                int current = vertex;
                vector<string> cyclePath;
                cyclePath.push_back(vertexNames[vertex]);
                
                while (current != neighbor && parent[current] != -1) {
                    cyclePath.push_back(vertexNames[parent[current]]);
                    current = parent[current];
                }
                
                for (int i = cyclePath.size() - 1; i >= 0; i--) {
                    cout << " -> " << cyclePath[i];
                }
                cout << " -> " << vertexNames[neighbor] << endl;
            }
            else if (color[neighbor] == WHITE) {
                parent[neighbor] = vertex;
                findAllCyclesUtil(neighbor, color, parent, backEdgeCount);
            }
        }

        color[vertex] = BLACK;
    }

public:
    /*
     * CHECK IF GRAPH IS A DAG (Directed Acyclic Graph)
     * A DAG has no cycles, useful for topological sorting
     */
    bool isDAG() {
        vector<Color> color(vertexCount, WHITE);
        
        for (int i = 0; i < vertexCount; i++) {
            if (color[i] == WHITE) {
                if (hasCycleFromVertex(i, color)) {
                    return false;
                }
            }
        }
        return true;
    }

private:
    bool hasCycleFromVertex(int vertex, vector<Color>& color) {
        color[vertex] = GRAY;
        
        for (int neighbor : adjList[vertex]) {
            if (color[neighbor] == GRAY) {
                return true;  // Cycle found
            }
            if (color[neighbor] == WHITE && hasCycleFromVertex(neighbor, color)) {
                return true;
            }
        }
        
        color[vertex] = BLACK;
        return false;
    }
};

int main() {
    cout << "=============================================" << endl;
    cout << "  Assignment 3 - Part B: Problem 2" << endl;
    cout << "  Cycle Detection in Directed Graph" << endl;
    cout << "=============================================" << endl;

    // Test Case 1: Graph WITH a cycle
    cout << "\n********** TEST CASE 1: Graph with Cycle **********" << endl;
    DirectedGraph graph1;

    graph1.addVertex("A");
    graph1.addVertex("B");
    graph1.addVertex("C");
    graph1.addVertex("D");
    graph1.addVertex("E");

    // Create edges forming a cycle: A -> B -> C -> D -> B
    graph1.addEdge("A", "B");
    graph1.addEdge("B", "C");
    graph1.addEdge("C", "D");
    graph1.addEdge("D", "B");  // This creates the cycle!
    graph1.addEdge("D", "E");

    graph1.displayGraph();
    graph1.detectCycle();
    graph1.findAllCycles();

    // Test Case 2: Graph WITHOUT a cycle (DAG)
    cout << "\n********** TEST CASE 2: Graph without Cycle (DAG) **********" << endl;
    DirectedGraph graph2;

    graph2.addVertex("1");
    graph2.addVertex("2");
    graph2.addVertex("3");
    graph2.addVertex("4");
    graph2.addVertex("5");

    // Create a DAG (no cycles)
    graph2.addEdge("1", "2");
    graph2.addEdge("1", "3");
    graph2.addEdge("2", "4");
    graph2.addEdge("3", "4");
    graph2.addEdge("4", "5");

    graph2.displayGraph();
    graph2.detectCycle();

    cout << "\nIs Graph 2 a DAG? " << (graph2.isDAG() ? "Yes" : "No") << endl;

    // Test Case 3: Graph with multiple cycles
    cout << "\n********** TEST CASE 3: Graph with Multiple Cycles **********" << endl;
    DirectedGraph graph3;

    graph3.addVertex("P");
    graph3.addVertex("Q");
    graph3.addVertex("R");
    graph3.addVertex("S");
    graph3.addVertex("T");

    // Create multiple cycles
    graph3.addEdge("P", "Q");
    graph3.addEdge("Q", "R");
    graph3.addEdge("R", "P");  // Cycle 1: P -> Q -> R -> P
    graph3.addEdge("R", "S");
    graph3.addEdge("S", "T");
    graph3.addEdge("T", "R");  // Cycle 2: R -> S -> T -> R

    graph3.displayGraph();
    graph3.detectCycle();
    graph3.findAllCycles();

    // Summary
    cout << "\n========== SUMMARY ==========" << endl;
    cout << "Cycle detection applications:" << endl;
    cout << "1. Deadlock detection in OS" << endl;
    cout << "2. Circular dependency check" << endl;
    cout << "3. Infinite loop detection" << endl;
    cout << "4. Course prerequisite validation" << endl;
    cout << "5. Package dependency resolution" << endl;
    cout << "==============================" << endl;

    return 0;
}
