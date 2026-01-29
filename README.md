# 🧩 Solving the Minimum Bisection Problem

## 📌 Overview
This project aims to solve the **Minimum Bisection Problem** on a given graph.

The program reads a graph from an input file and generates **four different solutions**, each produced by a distinct algorithmic approach.  
Each solution is written to a separate output file.

---

## ⚙️ Implemented Algorithms
The project implements the following methods:

1. **Exact algorithm**  
   Computes an optimal solution to the minimum bisection problem.

2. **Constructive heuristic**  
   Generates an initial feasible solution using a heuristic approach.

3. **Local search heuristic**  
   Improves the constructive solution by exploring its neighborhood.

4. **Tabu search**  
   Enhances the local search using tabu constraints to escape local optima.

---

## 🛠️ Compilation and Execution

### Requirements
- Linux environment (tested on **Debian**)
- `cmake`
- `make`

### Build instructions
From the root of the project, run:

```bash
$ sudo apt-get update && sudo apt-get install cmake make
$ cmake CMakeLists.txt
$ make
$ ./graph_project

```
📥 Program Usage
Once the program is running, you will be prompted to:

- Choose the graph representation : Matrix or Adjacency lists

- Provide the name or path of the input graph file
(without file extension)

Example in console:

```bash
Representation of the graph:
    1- Matrix
    2- Adjacency lists
>> 1

```
Path to the file to read graph's informations: test1

## 📤 Output Files
For an input file named test1, the program generates the following files in the working directory:

```bash
test1_exact.out
test1_constructive.out
test1_local_search.out
test1_tabu_search.out
```
-> Each file corresponds to one algorithmic approach.

🗂️ Project Structure
```bash
.
├── CMakeLists.txt
├── main.cpp
├── README.md
└── src
    ├── method
    │   ├── constructive
    │   │   ├── constructive.cpp
    │   │   └── constructive.h
    │   ├── exact
    │   │   ├── exact.cpp
    │   │   ├── exact.h
    │   │   └── pseudoCodeExactAlgo.txt
    │   ├── local_search
    │   │   ├── local_search.cpp
    │   │   └── local_search.h
    │   └── tabu_search
    │       ├── tabu_search.cpp
    │       └── tabu_search.h
    └── model
        └── Graph_class
            ├── Graph.cpp
            ├── Graph.h
            ├── Vertex.cpp
            └── Vertex.h
```
🎓 Academic Context
This project was developed as part of an academic course focusing on graph algorithms and optimization problems.
