//
// Created by bap on 06/10/2023.
//

#include "Vertex.h"

Vertex::Vertex(int val, int posInAdjMat): value(val), posInAdjMatrix(posInAdjMat), color('b'){}

void Vertex::setColor(char color){
    this->color = color;
}

Vertex::~Vertex() {
    std::vector<int>().swap(this->adjList);
    this->adjList.clear();
    this->adjList.shrink_to_fit();
}

int Vertex::getValue(){
    return this->value;
}

char Vertex::getColor(){
    return color;
}
vector<int> Vertex::getAdjList(){

    return this->adjList;
}

void Vertex::sortAdjList(){
    std::sort(this->adjList.begin(), this->adjList.end());
}

void Vertex::removeAdjList(int position){
    this->adjList.erase(this->adjList.begin()+position);
}

void Vertex::addAdjList(int val){
    this->adjList.push_back(val);
}


