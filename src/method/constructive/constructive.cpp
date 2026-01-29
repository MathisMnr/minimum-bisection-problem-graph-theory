//
// Created by vince on 22/11/2023.
//

#include "constructive.h"
void Graph::constructiveHeuristic() {
    int graphSize = this->getVertexList().size();

    this -> solutionMsb.edgesBetween = graphSize * graphSize;

//    cout << "Graph size: " << graphSize << endl;
    if (graphSize % 2 != 0) {
        cout << "Error: Graph size must be even" << endl;
        return;
    }


    // Initialize side
    char side = 'r'; // 'l' for left, 'r' for right

    // Initialize array of pairs (degree, vertex index) sorted by degree and complete it
    vector<pair<int, int>> arrayDegreVertex; //first: degree, second: vertex index
    for (int i = 0; i < graphSize; i++) {
        arrayDegreVertex.emplace_back(this->getAdjList(this->getVertexList()[i]->getValue()).size(), i);
    }
    sort(arrayDegreVertex.begin(), arrayDegreVertex.end(), greater<>());

    // For each vertex in the array of pairs, add it to the set with the least vertices and add its neighbors to the same set
    for (int i = 0; i < graphSize; i++){
        if(this->getVertexList()[arrayDegreVertex[i].second]->getColor() == 'b'){
            if(this->solutionMsb.set1.size() < graphSize/2  && side != 'l'){
                this->solutionMsb.set1.push_back(this->getVertexList()[arrayDegreVertex[i].second]);
                side = 'l';
            } else {
                this->solutionMsb.set2.push_back(this->getVertexList()[arrayDegreVertex[i].second]);
                side = 'r';
            }
            this->getVertexList()[arrayDegreVertex[i].second]->setColor('r');

            vector<int> adjList = this->getVertexList()[arrayDegreVertex[i].second]->getAdjList();
            for (int j = 0; j < adjList.size(); j++){
                if (adjList[j] != arrayDegreVertex[i].second && this->getVertexList()[adjList[j]]->getColor() == 'b'){
                    if (this->areLinked(arrayDegreVertex[i].second, adjList[j])) {
                        if(this->solutionMsb.set1.size() < graphSize/2  && side == 'l'){
                            this->solutionMsb.set1.push_back(this->getVertexList()[adjList[j]]);
                        } else {
                            this->solutionMsb.set2.push_back(this->getVertexList()[adjList[j]]);
                        }
                        this->getVertexList()[adjList[j]]->setColor('r');
                    }

                }
            }
        }
    }
    //Set the solution
    this->nbEdgesBetweenSets(this->solutionMsb.set1, this->solutionMsb.set2);
}