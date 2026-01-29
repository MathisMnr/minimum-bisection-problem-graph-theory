//
// Created by vince on 22/11/2023.
//

#include "tabu_search.h"
bool checkIfAlreadyUsed(const vector<pair<int, int>>& tabuList, pair<int, int> pair){
    for (auto & i : tabuList){
        if (i.first == pair.first && i.second == pair.second){
            return true;
        }
    }
    return false;
}

void Graph::tabuSearchHeuristic(){
    vector<pair<int, int>> tabuList;
    this->constructiveHeuristic();

    int nbOfVertex = this->getVertexList().size();
    int distance = getNbEdgesBetweenSets();

    random_device myRandomSeed;
    default_random_engine myRandomEngine(myRandomSeed());

    int noImprovement = 0;

    while (noImprovement < 10 && tabuList.size() < nbOfVertex/2){
        uniform_int_distribution<int> randomValue(0, nbOfVertex/2-1);
        uniform_int_distribution<int> randomValue2(0, nbOfVertex/2-1);
        if (!checkIfAlreadyUsed(tabuList, make_pair(randomValue(myRandomEngine), randomValue2(myRandomEngine)))) {
            tabuList.emplace_back(randomValue(myRandomEngine), randomValue2(myRandomEngine));
            this->swapVertex(randomValue(myRandomEngine), randomValue2(myRandomEngine));
            localSearchHeuristicForTabuSearch();
            if(distance < getNbEdgesBetweenSets()){
                this->swapVertex(randomValue(myRandomEngine), randomValue2(myRandomEngine));
                noImprovement++;
            }else{
                distance = getNbEdgesBetweenSets();
                noImprovement = 0;
            }
        }
    }
}