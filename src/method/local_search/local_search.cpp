//
// Created by vince on 22/11/2023.
//

#include "local_search.h"

void Graph::localSearchHeuristic() {

    //Constructive heuristique :
    constructiveHeuristic();

    // Calcul du nombre d'arêtes entre les deux ensembles :
    int numberCut = 0;
    for (auto v1 : this->solutionMsb.set1) {
        for (auto v2 : this->solutionMsb.set2) {
            if (areLinked(v1->getValue(), v2->getValue())) {
                numberCut++;
            }
        }
    }

    //this->displaySolutionMSB();

    // Boucle pour faire la recherche locale :
    bool verif = true;

    while (verif) {

        verif = false;

        // Parcourez tous les sommets et essayez de les échanger s'il y a un meilleur :
        for (int i = 0; i < getVertexList().size()/2 ; i++) {
            Vertex* currentVertex = getVertexList()[i];

            // Essayez de déplacer le sommet vers l'autre ensemble
            if (find(this->solutionMsb.set1.begin(), this->solutionMsb.set1.end(), currentVertex) != this->solutionMsb.set1.end()) {

                for (int j = 0; j < getVertexList().size()/2; j++) {

                    this->swapVertex(i, j);

                    // Calculez le nouveau nombre d'arêtes entre les ensembles après l'échange
                    int newNumberCut = 0;
                    for (auto v1 : this->solutionMsb.set1) {
                        for (auto v2 : this->solutionMsb.set2) {
                            if (areLinked(v1->getValue(), v2->getValue())) {
                                newNumberCut++;
                            }
                        }
                    }

                    // Si l'échange améliore la solution, effectuez l'échange
                    if (newNumberCut < numberCut) {
                        numberCut = newNumberCut;
                        verif = true;
                        break;  // Sortez de la boucle pour reprendre depuis le début
                    }

                    else{

                        // Annulez l'échange
                        this->swapVertex(i, j);

                    }
                }
            }
        }
    }

    this->nbEdgesBetweenSets(this->solutionMsb.set1, this->solutionMsb.set2);
    //this->displaySolutionMSB();

}
void Graph::localSearchHeuristicForTabuSearch(){

    // Calcul du nombre d'arêtes entre les deux ensembles :
    int numberCut = 0;
    for (auto v1 : this->solutionMsb.set1) {
        for (auto v2 : this->solutionMsb.set2) {
            if (areLinked(v1->getValue(), v2->getValue())) {
                numberCut++;
            }
        }
    }


    // Boucle pour faire la recherche locale :
    bool verif = true;

    while (verif) {

        verif = false;

        // Parcourez tous les sommets et essayez de les échanger s'il y a un meilleur :
        for (int i = 0; i < getVertexList().size()/2 ; i++) {
            Vertex* currentVertex = getVertexList()[i];

            // Essayez de déplacer le sommet vers l'autre ensemble
            if (find(this->solutionMsb.set1.begin(), this->solutionMsb.set1.end(), currentVertex) != this->solutionMsb.set1.end()) {

                for (int j = 0; j < getVertexList().size()/2; j++) {

                    this->swapVertex(i, j);

                    // Calculez le nouveau nombre d'arêtes entre les ensembles après l'échange
                    int newNumberCut = 0;
                    for (auto v1 : this->solutionMsb.set1) {
                        for (auto v2 : this->solutionMsb.set2) {
                            if (areLinked(v1->getValue(), v2->getValue())) {
                                newNumberCut++;
                            }
                        }
                    }

                    // Si l'échange améliore la solution, effectuez l'échange
                    if (newNumberCut < numberCut) {
                        numberCut = newNumberCut;
                        verif = true;
                        break;  // Sortez de la boucle pour reprendre depuis le début
                    }

                    else{

                        // Annulez l'échange
                        this->swapVertex(i, j);

                    }
                }
            }
        }
    }

    this->nbEdgesBetweenSets(this->solutionMsb.set1, this->solutionMsb.set2);
//    this->displaySolutionMSB();
}