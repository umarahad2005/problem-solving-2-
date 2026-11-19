# Problem Solving 2 — Data Structures & Algorithms in C++

Lab tasks and assignments for a Data Structures & Algorithms course, written in C++. Each folder holds standalone console programs (one `main()` per `.cpp` file); the `.docx`/`.pdf` files in the root are the matching lab and assignment write-ups.

## Contents

| Folder | Topic |
| --- | --- |
| `lab1` | Static and dynamic arrays, linear search, binary search, bubble and selection sort |
| `lab2` | Singly linked lists (insert at head/tail, display, update) |
| `lab3` | Linked list operations: delete by value, circular linked lists and reversal |
| `lab4` | Queues, plus simulations (bank queue, print queue, service queue, task queue) |
| `lab5` | Linked-list-based applications: playlist, browser history, text editor states, delivery route, turn system, priority queues (emergency room, print spooler) |
| `lab6` | Stacks: array and linked-list stacks, bracket matching, string reversal, infix to postfix/prefix, sorting a stack, two stacks in one array |
| `lab7` | Applied structures: news feed, file system, round-robin scheduler, shopping cart, order manager, form wizard |
| `lab8` | Binary trees and inorder / preorder / postorder traversals |
| `lab9` | General trees: product category tree, organisation tree, expression tree, social network |
| `lab10` | Graphs using an adjacency matrix (build, edge lookup) |
| `lab11` | Graphs using adjacency lists (build, edge lookup, edge count, removing connections) |
| `lab12` | Heaps / priority queues: ER triage, trading order book, trending hashtags, support tickets, surge pricing |
| `assignment 1` | Recursion/backtracking and strings: power set, Roman to integer, phone letter combinations, concatenated substrings |
| `assignment 2` | Priority queues and stacks: emergency call center, browser tab manager, airport security checkpoint, undo/redo system |
| `assignment 3` | Graph representations, BFS/DFS, cycle detection, topological sort |
| `assignment 4` | Shortest paths: Dijkstra (network delay time, cheapest flights) and Bellman-Ford (negative cycles, currency arbitrage) |

`h.html` is an unrelated standalone web page (a WebSocket-based camera/car control UI) that is not part of the C++ coursework.

## Building and running

Only the C++ standard library is used. With `g++` (C++17), compile and run any file on its own:

```bash
g++ -std=c++17 lab6/task5.cpp -o task5
./task5
```

The repository also includes a VS Code build task (`.vscode/tasks.json`) that compiles the active file with MSYS2 `g++` on Windows.
