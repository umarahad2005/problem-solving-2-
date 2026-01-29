/*
 * Assignment 3 - Part B: Problem 1 - BFS and DFS Traversal
 * Course: Problem Solving II (CS4703)
 * Riphah International University - BSCS 4th Semester
 * 
 * Problem Statement:
 * Implement Breadth-First Search (BFS) and Depth-First Search (DFS) traversals
 * on a graph. These are fundamental graph traversal algorithms used in many
 * applications like finding paths, connected components, and solving puzzles.
 * 
 * Graph Type: Directed Graph using Adjacency List
 * 
 * Logic:
 * - BFS: Uses a queue (FIFO) to explore nodes level by level
 *   Starting from source, visit all neighbors first, then their neighbors
 * 
 * - DFS: Uses a stack (LIFO) or recursion to explore as deep as possible
 *   Starting from source, go deep into one path before backtracking
 */

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <iomanip>
using namespace std;

class Graph {
private:
    vector<list<int>> adjList;
    vector<string> vertexNames;
    unordered_map<string, int> nameToIndex;
    int vertexCount;

public:
    Graph() : vertexCount(0) {}

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
     * BREADTH-FIRST SEARCH (BFS)
     * 
     * Algorithm:
     * 1. Start from a source vertex
     * 2. Use a queue to track vertices to visit
     * 3. Mark source as visited and enqueue it
     * 4. While queue is not empty:
     *    a. Dequeue a vertex, process it
     *    b. Enqueue all unvisited neighbors
     *    c. Mark them as visited
     * 
     * Time Complexity: O(V + E) where V = vertices, E = edges
     * Space Complexity: O(V) for the visited array and queue
     * 
     * Applications:
     * - Shortest path in unweighted graphs
     * - Level-order traversal
     * - Finding connected components
     * - Web crawlers
     */
    void BFS(const string& startVertex) {
        if (nameToIndex.find(startVertex) == nameToIndex.end()) {
            cout << "Start vertex not found!" << endl;
            return;
        }

        int startIdx = nameToIndex[startVertex];
        vector<bool> visited(vertexCount, false);
        queue<int> q;

        cout << "\n========== BFS TRAVERSAL ==========" << endl;
        cout << "Starting from vertex: " << startVertex << endl;
        cout << "\nStep-by-step execution:" << endl;
        cout << "----------------------------------------" << endl;

        visited[startIdx] = true;
        q.push(startIdx);
        cout << "1. Enqueue " << startVertex << " (starting vertex)" << endl;

        vector<string> traversalOrder;
        int step = 2;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            traversalOrder.push_back(vertexNames[current]);

            cout << step++ << ". Dequeue and visit: " << vertexNames[current];
            
            // Display queue state
            cout << " | Queue: [";
            queue<int> tempQ = q;
            bool first = true;
            while (!tempQ.empty()) {
                if (!first) cout << ", ";
                cout << vertexNames[tempQ.front()];
                tempQ.pop();
                first = false;
            }
            cout << "]" << endl;

            // Process all neighbors
            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                    cout << "   -> Enqueue neighbor: " << vertexNames[neighbor] << endl;
                }
            }
        }

        cout << "----------------------------------------" << endl;
        cout << "\nBFS Traversal Order: ";
        for (size_t i = 0; i < traversalOrder.size(); i++) {
            cout << traversalOrder[i];
            if (i < traversalOrder.size() - 1) cout << " -> ";
        }
        cout << endl;
        cout << "=====================================" << endl;
    }

    /*
     * DEPTH-FIRST SEARCH (DFS) - Recursive
     * 
     * Algorithm:
     * 1. Start from a source vertex
     * 2. Mark it as visited and process it
     * 3. Recursively visit each unvisited neighbor
     * 4. Backtrack when all neighbors are visited
     * 
     * Time Complexity: O(V + E)
     * Space Complexity: O(V) for visited array + O(V) for recursion stack
     * 
     * Applications:
     * - Topological sorting
     * - Cycle detection
     * - Path finding
     * - Strongly connected components
     */
    void DFSRecursive(const string& startVertex) {
        if (nameToIndex.find(startVertex) == nameToIndex.end()) {
            cout << "Start vertex not found!" << endl;
            return;
        }

        cout << "\n========== DFS TRAVERSAL (Recursive) ==========" << endl;
        cout << "Starting from vertex: " << startVertex << endl;
        cout << "\nStep-by-step execution:" << endl;
        cout << "------------------------------------------------" << endl;

        vector<bool> visited(vertexCount, false);
        vector<string> traversalOrder;
        int step = 1;

        DFSRecursiveUtil(nameToIndex[startVertex], visited, traversalOrder, step, 0);

        cout << "------------------------------------------------" << endl;
        cout << "\nDFS Traversal Order: ";
        for (size_t i = 0; i < traversalOrder.size(); i++) {
            cout << traversalOrder[i];
            if (i < traversalOrder.size() - 1) cout << " -> ";
        }
        cout << endl;
        cout << "================================================" << endl;
    }

private:
    void DFSRecursiveUtil(int vertex, vector<bool>& visited, 
                          vector<string>& order, int& step, int depth) {
        visited[vertex] = true;
        order.push_back(vertexNames[vertex]);

        // Indentation for recursion depth
        string indent(depth * 2, ' ');
        cout << indent << step++ << ". Visit: " << vertexNames[vertex] 
             << " (depth: " << depth << ")" << endl;

        for (int neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                cout << indent << "   -> Going deeper to: " << vertexNames[neighbor] << endl;
                DFSRecursiveUtil(neighbor, visited, order, step, depth + 1);
                cout << indent << "   <- Backtracking from: " << vertexNames[neighbor] << endl;
            }
        }
    }

public:
    /*
     * DEPTH-FIRST SEARCH (DFS) - Iterative using Stack
     * 
     * Algorithm:
     * 1. Push starting vertex onto stack
     * 2. While stack is not empty:
     *    a. Pop a vertex
     *    b. If not visited, mark as visited and process
     *    c. Push all unvisited neighbors onto stack
     */
    void DFSIterative(const string& startVertex) {
        if (nameToIndex.find(startVertex) == nameToIndex.end()) {
            cout << "Start vertex not found!" << endl;
            return;
        }

        int startIdx = nameToIndex[startVertex];
        vector<bool> visited(vertexCount, false);
        stack<int> s;

        cout << "\n========== DFS TRAVERSAL (Iterative) ==========" << endl;
        cout << "Starting from vertex: " << startVertex << endl;
        cout << "\nStep-by-step execution:" << endl;
        cout << "------------------------------------------------" << endl;

        s.push(startIdx);
        cout << "1. Push " << startVertex << " onto stack" << endl;

        vector<string> traversalOrder;
        int step = 2;

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;
                traversalOrder.push_back(vertexNames[current]);

                cout << step++ << ". Pop and visit: " << vertexNames[current];
                
                // Display stack state
                cout << " | Stack: [";
                stack<int> tempS = s;
                vector<string> stackContents;
                while (!tempS.empty()) {
                    stackContents.push_back(vertexNames[tempS.top()]);
                    tempS.pop();
                }
                for (int i = stackContents.size() - 1; i >= 0; i--) {
                    cout << stackContents[i];
                    if (i > 0) cout << ", ";
                }
                cout << "]" << endl;

                // Push neighbors in reverse order for correct traversal
                vector<int> neighbors(adjList[current].begin(), adjList[current].end());
                for (int i = neighbors.size() - 1; i >= 0; i--) {
                    if (!visited[neighbors[i]]) {
                        s.push(neighbors[i]);
                        cout << "   -> Push neighbor: " << vertexNames[neighbors[i]] << endl;
                    }
                }
            }
        }

        cout << "------------------------------------------------" << endl;
        cout << "\nDFS Traversal Order: ";
        for (size_t i = 0; i < traversalOrder.size(); i++) {
            cout << traversalOrder[i];
            if (i < traversalOrder.size() - 1) cout << " -> ";
        }
        cout << endl;
        cout << "================================================" << endl;
    }

    // BFS to find shortest path in unweighted graph
    void BFSShortestPath(const string& source, const string& destination) {
        if (nameToIndex.find(source) == nameToIndex.end() ||
            nameToIndex.find(destination) == nameToIndex.end()) {
            cout << "Vertex not found!" << endl;
            return;
        }

        int srcIdx = nameToIndex[source];
        int destIdx = nameToIndex[destination];

        vector<bool> visited(vertexCount, false);
        vector<int> parent(vertexCount, -1);
        queue<int> q;

        visited[srcIdx] = true;
        q.push(srcIdx);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == destIdx) {
                // Reconstruct path
                vector<string> path;
                int node = destIdx;
                while (node != -1) {
                    path.push_back(vertexNames[node]);
                    node = parent[node];
                }

                cout << "\n========== SHORTEST PATH (BFS) ==========" << endl;
                cout << "From " << source << " to " << destination << ":" << endl;
                cout << "Path: ";
                for (int i = path.size() - 1; i >= 0; i--) {
                    cout << path[i];
                    if (i > 0) cout << " -> ";
                }
                cout << "\nPath length: " << path.size() - 1 << " edges" << endl;
                cout << "==========================================" << endl;
                return;
            }

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }

        cout << "No path exists from " << source << " to " << destination << endl;
    }
};

int main() {
    cout << "=============================================" << endl;
    cout << "  Assignment 3 - Part B: Problem 1" << endl;
    cout << "  BFS and DFS Graph Traversal" << endl;
    cout << "=============================================" << endl;

    Graph graph;

    // Create a sample graph
    cout << "\n--- Creating Graph ---" << endl;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");
    graph.addVertex("F");

    // Add edges to create an interesting graph
    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("B", "D");
    graph.addEdge("B", "E");
    graph.addEdge("C", "F");
    graph.addEdge("D", "E");
    graph.addEdge("E", "F");

    // Display the graph
    graph.displayGraph();

    // Perform BFS
    graph.BFS("A");

    // Perform DFS (Recursive)
    graph.DFSRecursive("A");

    // Perform DFS (Iterative)
    graph.DFSIterative("A");

    // Find shortest path using BFS
    graph.BFSShortestPath("A", "F");
    graph.BFSShortestPath("B", "F");

    // Comparison summary
    cout << "\n========== BFS vs DFS COMPARISON ==========" << endl;
    cout << "| Feature          | BFS              | DFS              |" << endl;
    cout << "|-----------------|------------------|------------------|" << endl;
    cout << "| Data Structure  | Queue (FIFO)     | Stack (LIFO)     |" << endl;
    cout << "| Traversal       | Level by level   | Deep then back   |" << endl;
    cout << "| Shortest Path   | Yes (unweighted) | No               |" << endl;
    cout << "| Memory          | O(width)         | O(depth)         |" << endl;
    cout << "| Use Case        | Shortest path    | Cycle detection  |" << endl;
    cout << "==============================================" << endl;

    return 0;
}
