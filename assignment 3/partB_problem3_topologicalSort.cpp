/*
 * Assignment 3 - Part B: Problem 3 - Topological Sort
 * Course: Problem Solving II (CS4703)
 * Riphah International University - BSCS 4th Semester
 * 
 * Problem Statement:
 * Perform topological sorting on a Directed Acyclic Graph (DAG).
 * Topological sort produces a linear ordering of vertices such that
 * for every directed edge (u, v), vertex u comes before v in the ordering.
 * 
 * Graph Type: Directed Acyclic Graph (DAG) using Adjacency List
 * 
 * Logic:
 * Two approaches implemented:
 * 
 * 1. DFS-based (Kahn's predecessor):
 *    - Perform DFS and add vertices to stack after all descendants visited
 *    - Pop stack to get topological order
 * 
 * 2. Kahn's Algorithm (BFS-based):
 *    - Find all vertices with in-degree 0
 *    - Remove them one by one, reducing in-degrees of neighbors
 *    - If not all vertices processed, cycle exists
 * 
 * Applications:
 * - Task scheduling with dependencies
 * - Build systems (Makefiles, Maven, etc.)
 * - Course scheduling with prerequisites
 * - Spreadsheet cell evaluation order
 */

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <string>
#include <unordered_map>
#include <iomanip>
using namespace std;

class DAG {
private:
    vector<list<int>> adjList;
    vector<string> vertexNames;
    unordered_map<string, int> nameToIndex;
    int vertexCount;

public:
    DAG() : vertexCount(0) {}

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
        cout << "Interpretation: A -> B means A must come before B" << endl;
        cout << "--------------------------------------" << endl;
        for (int i = 0; i < vertexCount; i++) {
            cout << vertexNames[i] << " -> ";
            bool first = true;
            for (int neighbor : adjList[i]) {
                if (!first) cout << ", ";
                cout << vertexNames[neighbor];
                first = false;
            }
            if (adjList[i].empty()) cout << "(no dependencies)";
            cout << endl;
        }
        cout << "======================================" << endl;
    }

    /*
     * TOPOLOGICAL SORT USING DFS
     * 
     * Algorithm:
     * 1. Perform DFS from each unvisited vertex
     * 2. After visiting all descendants of a vertex, push it to stack
     * 3. The stack contains vertices in reverse topological order
     * 4. Pop stack to get topological order
     * 
     * Time Complexity: O(V + E)
     * Space Complexity: O(V) for visited array and stack
     */
    vector<string> topologicalSortDFS() {
        cout << "\n========== TOPOLOGICAL SORT (DFS Method) ==========" << endl;
        cout << "Using post-order DFS with stack" << endl;
        cout << "--------------------------------------------------" << endl;

        vector<bool> visited(vertexCount, false);
        stack<int> resultStack;

        // Perform DFS from each unvisited vertex
        for (int i = 0; i < vertexCount; i++) {
            if (!visited[i]) {
                cout << "\nStarting DFS from: " << vertexNames[i] << endl;
                topologicalSortDFSUtil(i, visited, resultStack);
            }
        }

        // Extract result from stack
        vector<string> result;
        cout << "\n--------------------------------------------------" << endl;
        cout << "Popping from stack (topological order):" << endl;

        int order = 1;
        while (!resultStack.empty()) {
            result.push_back(vertexNames[resultStack.top()]);
            cout << order++ << ". " << vertexNames[resultStack.top()] << endl;
            resultStack.pop();
        }

        cout << "\nTopological Order: ";
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) cout << " -> ";
        }
        cout << endl;
        cout << "==================================================" << endl;

        return result;
    }

private:
    void topologicalSortDFSUtil(int vertex, vector<bool>& visited, stack<int>& resultStack) {
        visited[vertex] = true;
        cout << "  Visiting: " << vertexNames[vertex] << endl;

        // Visit all neighbors first (descendants)
        for (int neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                cout << "    -> Going to neighbor: " << vertexNames[neighbor] << endl;
                topologicalSortDFSUtil(neighbor, visited, resultStack);
            }
        }

        // After all descendants visited, push to stack
        resultStack.push(vertex);
        cout << "  Pushing to stack: " << vertexNames[vertex] 
             << " (all descendants visited)" << endl;
    }

public:
    /*
     * TOPOLOGICAL SORT USING KAHN'S ALGORITHM (BFS-based)
     * 
     * Algorithm:
     * 1. Calculate in-degree of all vertices
     * 2. Add all vertices with in-degree 0 to a queue
     * 3. While queue is not empty:
     *    a. Remove vertex from queue, add to result
     *    b. Reduce in-degree of all neighbors
     *    c. If any neighbor's in-degree becomes 0, add to queue
     * 4. If result size != number of vertices, cycle exists
     * 
     * Time Complexity: O(V + E)
     * Space Complexity: O(V) for in-degree array and queue
     */
    vector<string> topologicalSortKahn() {
        cout << "\n========== TOPOLOGICAL SORT (Kahn's Algorithm) ==========" << endl;
        cout << "Using BFS with in-degree tracking" << endl;
        cout << "----------------------------------------------------------" << endl;

        // Calculate in-degrees
        vector<int> inDegree(vertexCount, 0);
        for (int i = 0; i < vertexCount; i++) {
            for (int neighbor : adjList[i]) {
                inDegree[neighbor]++;
            }
        }

        // Display initial in-degrees
        cout << "\nInitial in-degrees:" << endl;
        for (int i = 0; i < vertexCount; i++) {
            cout << "  " << vertexNames[i] << ": " << inDegree[i] << endl;
        }

        // Add all vertices with in-degree 0 to queue
        queue<int> q;
        cout << "\nVertices with in-degree 0 (starting points):" << endl;
        for (int i = 0; i < vertexCount; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
                cout << "  " << vertexNames[i] << endl;
            }
        }

        vector<string> result;
        int processedCount = 0;

        cout << "\nProcessing order:" << endl;
        cout << "----------------------------------------------------------" << endl;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            result.push_back(vertexNames[current]);
            processedCount++;

            cout << processedCount << ". Process: " << vertexNames[current] << endl;

            // Reduce in-degree of neighbors
            for (int neighbor : adjList[current]) {
                inDegree[neighbor]--;
                cout << "   -> Reduce in-degree of " << vertexNames[neighbor] 
                     << " to " << inDegree[neighbor] << endl;
                
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                    cout << "      (Added to queue - in-degree became 0)" << endl;
                }
            }
        }

        cout << "----------------------------------------------------------" << endl;

        // Check for cycle
        if (processedCount != vertexCount) {
            cout << "\n*** WARNING: Cycle detected! Not all vertices processed. ***" << endl;
            cout << "Processed: " << processedCount << " / " << vertexCount << endl;
            return {};
        }

        cout << "\nTopological Order: ";
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) cout << " -> ";
        }
        cout << endl;
        cout << "==========================================================" << endl;

        return result;
    }

    // Get all possible topological orderings (for small graphs)
    void allTopologicalSorts() {
        cout << "\n========== ALL TOPOLOGICAL ORDERINGS ==========" << endl;

        vector<int> inDegree(vertexCount, 0);
        for (int i = 0; i < vertexCount; i++) {
            for (int neighbor : adjList[i]) {
                inDegree[neighbor]++;
            }
        }

        vector<bool> visited(vertexCount, false);
        vector<int> result;
        int count = 0;

        allTopologicalSortsUtil(inDegree, visited, result, count);

        cout << "\nTotal valid topological orderings: " << count << endl;
        cout << "================================================" << endl;
    }

private:
    void allTopologicalSortsUtil(vector<int>& inDegree, vector<bool>& visited,
                                 vector<int>& result, int& count) {
        bool flag = false;

        for (int i = 0; i < vertexCount; i++) {
            if (inDegree[i] == 0 && !visited[i]) {
                // Choose this vertex
                visited[i] = true;
                result.push_back(i);

                // Reduce in-degree of neighbors
                for (int neighbor : adjList[i]) {
                    inDegree[neighbor]--;
                }

                // Recurse
                allTopologicalSortsUtil(inDegree, visited, result, count);

                // Backtrack
                visited[i] = false;
                result.pop_back();
                for (int neighbor : adjList[i]) {
                    inDegree[neighbor]++;
                }

                flag = true;
            }
        }

        // If all vertices are visited, we found a valid ordering
        if (!flag && result.size() == (size_t)vertexCount) {
            count++;
            cout << count << ". ";
            for (size_t i = 0; i < result.size(); i++) {
                cout << vertexNames[result[i]];
                if (i < result.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "=============================================" << endl;
    cout << "  Assignment 3 - Part B: Problem 3" << endl;
    cout << "  Topological Sort on DAG" << endl;
    cout << "=============================================" << endl;

    // Example 1: Course Prerequisites
    cout << "\n********** EXAMPLE 1: Course Prerequisites **********" << endl;
    cout << "Scenario: Schedule courses based on prerequisites" << endl;

    DAG courseGraph;

    // Add courses
    courseGraph.addVertex("Math101");
    courseGraph.addVertex("CS101");
    courseGraph.addVertex("CS201");
    courseGraph.addVertex("CS301");
    courseGraph.addVertex("Physics101");
    courseGraph.addVertex("CS401");

    // Add prerequisites (edge A->B means A is prerequisite for B)
    courseGraph.addEdge("Math101", "CS101");
    courseGraph.addEdge("Math101", "Physics101");
    courseGraph.addEdge("CS101", "CS201");
    courseGraph.addEdge("Physics101", "CS201");
    courseGraph.addEdge("CS201", "CS301");
    courseGraph.addEdge("CS301", "CS401");

    courseGraph.displayGraph();
    courseGraph.topologicalSortDFS();
    courseGraph.topologicalSortKahn();

    // Example 2: Build Dependencies
    cout << "\n********** EXAMPLE 2: Build Dependencies **********" << endl;
    cout << "Scenario: Determine build order for software modules" << endl;

    DAG buildGraph;

    buildGraph.addVertex("libA");
    buildGraph.addVertex("libB");
    buildGraph.addVertex("libC");
    buildGraph.addVertex("app1");
    buildGraph.addVertex("app2");

    // libA and libB are independent
    // libC depends on libA and libB
    // app1 depends on libC
    // app2 depends on libB and libC
    buildGraph.addEdge("libA", "libC");
    buildGraph.addEdge("libB", "libC");
    buildGraph.addEdge("libC", "app1");
    buildGraph.addEdge("libB", "app2");
    buildGraph.addEdge("libC", "app2");

    buildGraph.displayGraph();
    buildGraph.topologicalSortKahn();
    buildGraph.allTopologicalSorts();

    // Example 3: Task Scheduling
    cout << "\n********** EXAMPLE 3: Task Scheduling **********" << endl;
    cout << "Scenario: Project tasks with dependencies" << endl;

    DAG taskGraph;

    taskGraph.addVertex("Design");
    taskGraph.addVertex("Code");
    taskGraph.addVertex("Test");
    taskGraph.addVertex("Document");
    taskGraph.addVertex("Deploy");

    taskGraph.addEdge("Design", "Code");
    taskGraph.addEdge("Design", "Document");
    taskGraph.addEdge("Code", "Test");
    taskGraph.addEdge("Test", "Deploy");
    taskGraph.addEdge("Document", "Deploy");

    taskGraph.displayGraph();
    taskGraph.topologicalSortDFS();
    taskGraph.allTopologicalSorts();

    // Summary
    cout << "\n========== SUMMARY ==========" << endl;
    cout << "Topological Sort Applications:" << endl;
    cout << "1. Course/exam scheduling" << endl;
    cout << "2. Build systems (Make, Maven, Gradle)" << endl;
    cout << "3. Task scheduling with dependencies" << endl;
    cout << "4. Spreadsheet formula evaluation" << endl;
    cout << "5. Symbol resolution in linkers" << endl;
    cout << "\nKey Points:" << endl;
    cout << "- Only works on DAGs (Directed Acyclic Graphs)" << endl;
    cout << "- Multiple valid orderings may exist" << endl;
    cout << "- DFS method: O(V+E) time, uses stack" << endl;
    cout << "- Kahn's method: O(V+E) time, uses queue" << endl;
    cout << "==============================" << endl;

    return 0;
}
