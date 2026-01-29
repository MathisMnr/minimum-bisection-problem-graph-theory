//
// Created by vince on 22/11/2023.
//

#ifndef THE_BEST_PROJECT_EXACT_H
#define THE_BEST_PROJECT_EXACT_H
#include "../../model/Graph_class/Graph.h"
#include <map>
#include <chrono>
#include <fstream>

int pwr(int base,int exp);
int factorielle(int nb);
int sum2PwrN(int a, int b);
int getMostLeft1Pos(int myNumber, int nbBits);
int getMostRight1Pos(int nbr);
int nbOne(int myBin, int nbBits);
int countZeroOnLeft(int myBin, int posOf1, int * pposOfFirst0= nullptr, int * pposOfLastZeo= nullptr);
void convertToBinary(unsigned int n);
void generateSetsRightShift(int myBin, int nbBits, int pos1moving, Graph* G, vector<map<string, int>> restoreMyBin =vector<map<string, int>>());
void generateSetsLeftShift(int myBin, int nbBits, int pos1moving, Graph* G, vector<map<string, int>> restoreMyBin =vector<map<string, int>>());
void test(void (Graph::*pF)(), int nbVerticesMax, int nbInstances2Run4EachTest);
void buildGraphFromFile(string filePath, Graph* G);
void solution2File(string fileName, Graph* G);
#endif //THE_BEST_PROJECT_EXACT_H
