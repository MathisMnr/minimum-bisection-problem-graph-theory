//
// Created by bap on 06/10/2023.
//

#ifndef PROJET_VERTEX_H
#define PROJET_VERTEX_H
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <random>
using namespace std;


class Vertex {
private:
    int value;
    char color;
    vector<int> adjList;
    int posInAdjMatrix;

    friend class Graph;
    Vertex(int value, int posInAdjMatrix);
    void setColor(char color);

public:
    ~Vertex();
    int getValue();
    char getColor();
    vector<int> getAdjList();
    void sortAdjList();
    void removeAdjList(int position);
    void addAdjList(int val);
};


#endif //PROJET_VERTEX_H
