//
// Created by bap on 06/10/2023.
//

#include "Graph.h"

Graph::Graph(unsigned int n, const char mod): mode(mod){
    for (int i = 0;i < n;i++){
        this->addVertex();
    }
}

Graph::Graph(const char mod): mode(mod){}

Graph::~Graph(){
    std::vector<Vertex*>::iterator it = this->vertexList.begin();
    for (auto  vertex : this->vertexList){
        delete vertex;
    }
}

const char Graph::getMode(){
    return mode;
}

solutionMSB Graph::getSolutionMDB(){
    return this->solutionMsb;
}

void Graph::addVertex(){
    Vertex* w = new Vertex(vertexCount, vertexList.size());
    if (mode == 'm'){
        vector<int> newLineInAdjMatrix(this->adjMatrix.size(), 0);
        /*
        for (int i = 0; i < this->adjMatrix.size();i++){
            newLineInAdjMatrix.push_back(0);
        }*/
        this->adjMatrix.push_back(newLineInAdjMatrix);
        for (int i = 0; i < this->adjMatrix.size();i++){
            this->adjMatrix[i].push_back(0);
        }
    }
    this->vertexList.push_back(w);
    vertexCount++;

}

void Graph::delVertex(int valVertex){
    Vertex* vertex2Del;
    int vertex2DelPos;
    for (int i=0;i< this->getVertexList().size();i++){
        if (this->getVertexList()[i]->getValue() == valVertex){
            vertex2DelPos = i;
            break;
        }
    }
    vertex2Del = this->getVertexList()[vertex2DelPos];
    switch (mode) {
        case 'l':
            for (int valVertex2: this->getAdjList(vertex2Del->getValue())){
                this->removeEdge(valVertex, valVertex2);
            }
            break;

        case 'm':
            for (int line = 0; line < this->adjMatrix.size();line++){
                this->adjMatrix[line].erase(this->adjMatrix[line].begin()+vertex2DelPos);
                if (line > vertex2DelPos){
                    vertexList[line]->posInAdjMatrix--;
                }
            }
            this->adjMatrix.erase(this->adjMatrix.begin()+vertex2DelPos);
            break;

    }
    delete vertex2Del;
    this->vertexList.erase(this->vertexList.begin()+vertex2DelPos);

}

Vertex* Graph::getVertex(int valVertex){
    for (auto vertex: this->vertexList){
        if (vertex->getValue() == valVertex){
            return vertex;
        }
    }
}

int Graph::getvertexCount(){
    return vertexCount;
}

vector<int> Graph::getAdjList(int vertexVal){
    switch (this->mode){
        case 'l':
            return this->getVertex(vertexVal)->adjList;
        case 'm':
            vector<int> myAdjList = this->adjMatrix[this->getVertex(vertexVal)->posInAdjMatrix];
            return myAdjList;
    }
}

void Graph::display(){
    std::cout << "Vertex:" << std::endl;
    switch (mode) {
        case 'l':
            for (auto vertex: this->vertexList){
                std::cout << "Edges of " << vertex->getValue() << ": ";
                for (int vertexEdge: this->getAdjList(vertex->getValue())){
                    std::cout << vertexEdge << " ";
                }
                std::cout << std::endl;
            }
            break;

        case 'm':
            for (int i = 0; i< this->adjMatrix.size();i++){
                std::cout << "Edges of " << this->vertexList[i]->getValue() << ": ";
                for (int j = 0; j< this->adjMatrix[i].size();j++){
                    if (this->adjMatrix[i][j] == 1){
                        std::cout << this->vertexList[j]->getValue() << " ";
                    }
                }
                cout << endl;
            }
            break;
    }


}


vector<Vertex*> Graph::getVertexList(){
    return this->vertexList;
}

bool Graph::addEdge(int valVertex1, int valVertex2){
    Vertex* v = this->getVertex(valVertex1);
    Vertex* w = this->getVertex(valVertex2);
    int posV = v->posInAdjMatrix;
    int posW = w->posInAdjMatrix;
    switch (mode) {
        case 'l':
            if (valVertex1 == valVertex2){
                return false;
            }
            for (int vertexLinked: this->getAdjList(v->getValue())){
                if (vertexLinked == w->getValue())
                    return false;
            }
            v->addAdjList(valVertex2);
            w->addAdjList(valVertex1);
            break;

        case 'm':
            this->adjMatrix[posV][posW] = 1;
            this->adjMatrix[posW][posV] = 1;
            break;
    }
    return true;

}

bool Graph::removeEdge(int valVertex1, int valVertex2){
    Vertex* v = this->getVertex(valVertex1);
    Vertex* w = this->getVertex(valVertex2);
    vector<int> vAdjList = this->getAdjList(valVertex1);
    vector<int> wAdjList = this->getAdjList(valVertex2);
    int posV = v->posInAdjMatrix;
    int posW = w->posInAdjMatrix;
    switch (mode) {
        case 'l':
            if (valVertex1 == valVertex2){
                return false;
            }
            for (int i = 0; i < vAdjList.size();i++){
                if (vAdjList[i] == w->getValue()){
                    v->removeAdjList(i);
                    for (int j = 0; j < wAdjList.size();j++){
                        if (wAdjList[j] == v->getValue()){
                            w->removeAdjList(j);
                            return true;
                        }
                    }
                }
            }
            return false;
            break;

        case 'm':
            this->adjMatrix[posV][posW] = 0;
            this->adjMatrix[posW][posV] = 0;
            break;
    }



}

bool Graph::areLinked(int valVertex1, int valVertex2){
    Vertex* v = this->getVertex(valVertex1);
    Vertex* w = this->getVertex(valVertex2);
    switch (mode) {
        case 'l':
            for (int vertexLinked: this->getAdjList(w->getValue())){
                if (vertexLinked == v->getValue()){
                    return true;
                }
            }
            break;

        case 'm':
            switch (this->adjMatrix[v->posInAdjMatrix][w->posInAdjMatrix]) {
                case 1:
                    return true;
            }
            break;
    }
    return false;

}
void Graph::swapVertex(int val1, int val2){
    Vertex* stock = this->solutionMsb.set1[val1];
    this->solutionMsb.set1[val1] = this->solutionMsb.set2[val2];
    this->solutionMsb.set2[val2] = stock;
}
void Graph::DFS_Visit(Vertex* v){
    v->setColor('w');
    v->sortAdjList();
    for (int i = 0; i < this->getAdjList(v->getValue()).size(); i++) {
        Vertex *curr_v = this->getVertex(this->getAdjList(v->getValue())[i]);
        if (curr_v->getColor() == 'b') {
           DFS_Visit(curr_v);
        }
    }
    v->setColor('r');
    std::cout << v->getValue() << " ";
}

void Graph::DFS_main(){
    for(int i=0;i<this->getVertexList().size();i++){
        this->getVertexList()[i]->setColor('b');
    }
    for(int i=0;i<this->getVertexList().size();i++){
        if (this->getVertexList()[i]->getColor() == 'b'){
            DFS_Visit(this->getVertexList()[i]);
        }
    }
}

void Graph::displaySolutionMSB(){

    cout << "Set 1: ";
    for (auto vertex: this->solutionMsb.set1){
        cout << vertex->getValue() << " ";
    }
    cout << endl  << "size : " << this->solutionMsb.set1.size() << endl;
    cout << "Set 2: ";
    for (auto vertex: this->solutionMsb.set2){
        cout << vertex->getValue() << " ";
    }
    cout << endl  << "size : "<< this->solutionMsb.set2.size() << endl;

    cout << "Edges between sets: " << this->solutionMsb.edgesBetween << endl;
}

//Calculate number of edges between two sets
void Graph::nbEdgesBetweenSets(vector<Vertex *> set1, vector<Vertex*> set2){
    int nbEdges = 0;
    for (auto vertexInSet1: set1){
        for(auto vertexInSet2: set2){
            if (this->areLinked(vertexInSet1->getValue(), vertexInSet2->getValue())){
                nbEdges++;
            }
            if (nbEdges > this->solutionMsb.edgesBetween){
                return;
            }
        }
    }
    this->solutionMsb.edgesBetween = nbEdges;
    this->solutionMsb.set1 = set1;
    this->solutionMsb.set2 = set2;


//    cout << "set1 size : " << set1.size() << endl;
//    cout << "set2 size : " << set2.size() << endl;
//    cout << "nbEdgesBetween : " << nbEdges << endl;
}

int Graph::getNbEdgesBetweenSets() {
    return this->solutionMsb.edgesBetween;
}