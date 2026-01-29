//
// Created by bap on 06/10/2023.
//

#ifndef PROJET_GRAPH_H
#define PROJET_GRAPH_H
#include "Vertex.h"

typedef struct {
    vector<Vertex*> set1;
    vector<Vertex*> set2;
    int edgesBetween;
} solutionMSB;

class Graph {
private:
    vector<Vertex*> vertexList;
    int vertexCount = 0;
    solutionMSB solutionMsb;
    const char mode;
    vector<vector<int>> adjMatrix;

//    vector<Vertex*> set1;
//    vector<Vertex*> set2;

public:
    Graph(unsigned int n, const char mod);
    Graph(const char mod);
    ~Graph();
    const char getMode();
    solutionMSB getSolutionMDB();
    void addVertex();
    void delVertex(int valVertex2);
    Vertex* getVertex(int value);
    int getvertexCount();
    void display();
    vector<Vertex*> getVertexList();
    bool addEdge(int val1, int val2);
    bool removeEdge(int val1, int val2);
    bool areLinked(int valVertex1, int valVertex2);
    void swapVertex(int val1, int val2);

    void DFS_Visit(Vertex* v);
    void DFS_main();

    vector<int> getAdjList(int vertexVal);

    void exactSolutionMSB();
    void isExactSolutionBetter(int myBin);
    void localSearchHeuristic();
    void localSearchHeuristicForTabuSearch();
    void constructiveHeuristic();
    void tabuSearchHeuristic();

    void displaySolutionMSB();
    void nbEdgesBetweenSets(vector<Vertex *> set1, vector<Vertex*> set2);
    int getNbEdgesBetweenSets();

};


#endif //PROJET_GRAPH_H
