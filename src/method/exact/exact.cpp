//
// Created by vince on 22/11/2023.
//

#include "exact.h"

//Math function power
int pwr(int base,int exp) {
    int res=1;

    while(exp>=1) {
        res*=base;
        exp--;
    }
    return res;
}

int factorielle(int nb){
    int res = 1;
    for (int i = 1;i <= nb;i++){
        res *= i;
    }
    return res;
}

//Sum of 2^n with a <= n < b
int sum2PwrN(int a, int b){
    int sum = 0;
    for (int i = a; i<=b;i++){
        sum+= pwr(2, i);
    }
    return sum;
}

//Get position of the most left 1 in myBin
int getMostLeft1Pos(int myNumber, int nbBitss){
    nbBitss--;
    while ((myNumber >> nbBitss) != 1){
        nbBitss--;
    }
    return nbBitss;
}

//Get position of the most right 1 in myBin
int getMostRight1Pos(int nbr){
    int i = 0;
    while (((nbr >>i) & 1 ) == 0){
        i++;
    }
    return i;
}

//Number of one in myBin (not always nbBits/2, it might change when we are shifting some bits on left from the shifting_right function)
int nbOne(int myBin, int nbBits){
    int n = 0;
    for (int i = 0; i < nbBits;i++){
        if (((myBin & (1 << i)) >> i) == 1){
            n++;
        }
    }
    return n;
}

//Count the number of 0 on the left until we find a 1, starting from the bit posOf1 in myBin
int countZeroOnLeft(int myBin, int posOf1, int * pposOfFirst0, int * pposOfLastZeo){
    int i = 0;
    int n = 0;
    while (((myBin & (1 << (posOf1+i))) >> (posOf1+i)) == 1){
        i++;
    }
    if (pposOfFirst0 != nullptr){
        *pposOfFirst0 = posOf1+i;
    }
    while(((myBin & (1 << (posOf1+i))) >> (posOf1+i)) == 0){
        i++;
        n++;
    }
    if (pposOfLastZeo != nullptr){
        *pposOfLastZeo = posOf1+i-1;
    }
    return n;

}

void convertToBinary(unsigned int n)
{
    if (n / 2 != 0) {
        convertToBinary(n / 2);
    }
    printf("%d", n % 2);
}

//Check if the solution (myBin) is better than the current one
void Graph::isExactSolutionBetter(int myBin){
    vector<Vertex*> set1, set2;
    int edgesBetween = 0;
    int lastindexVertexInSet1Compared = 0;
    int lastindexVertexInSet2Compared = 0;
    int indexVertexInSet1 = -1;
    int indexVertexInSet2 = -1;
    bool init = false;
    int nbBits = this->vertexList.size();
    //Generating sets from binary number, if the bit if 0 we put it in set1 otherwise if it's 1 it goes in set2
    for (int i = 0; i < nbBits;i++){
        switch ((myBin & (1 << i)) >> i) {
            case 0:
                indexVertexInSet1++;
                set1.push_back(this->getVertexList()[i]);
                break;
            case 1:
                indexVertexInSet2++;
                set2.push_back(this->getVertexList()[i]);
        }
        //optimisation (counting edges while building sets), can be replaced with the line edgesBetween = nbEdgesBetweenSets(set1, set2); when living the loop
        if (indexVertexInSet1 != -1 && indexVertexInSet2 != -1){
            if (!init){
                if( indexVertexInSet1 == 0){
                    for (int j=0; j<=indexVertexInSet2;j++){
                        if (this->areLinked(set1[0]->getValue(), set2[j]->getValue())){
                            edgesBetween++;
                            if ( edgesBetween >= this->solutionMsb.edgesBetween || edgesBetween == -1){
                                return;
                            }
                        }
                    }
                }
                else if( indexVertexInSet2 == 0){
                    for (int j=0; j<=indexVertexInSet1;j++){
                        if (this->areLinked(set2[0]->getValue(), set1[j]->getValue())){
                            edgesBetween++;
                            if ( edgesBetween >= this->solutionMsb.edgesBetween || edgesBetween == -1){
                                return;
                            }
                        }
                    }
                }
                init = true;
            }
            else{
                if( indexVertexInSet1 != lastindexVertexInSet1Compared){
                    for (int j = 0;j<=indexVertexInSet2;j++){
                        if (this->areLinked(set1[indexVertexInSet1]->getValue(), set2[j]->getValue())){
                            edgesBetween++;
                            if ( edgesBetween >= this->solutionMsb.edgesBetween || edgesBetween == -1){
                                return;
                            }
                        }
                    }
                }
                else if( indexVertexInSet2 != lastindexVertexInSet2Compared){
                    for (int j = 0;j<=indexVertexInSet1;j++){
                        if (this->areLinked(set2[indexVertexInSet2]->getValue(), set1[j]->getValue())){
                            edgesBetween++;
                            if ( edgesBetween >= this->solutionMsb.edgesBetween || edgesBetween == -1){
                                return;
                            }
                        }
                    }
                }
            }

            lastindexVertexInSet1Compared = indexVertexInSet1;
            lastindexVertexInSet2Compared = indexVertexInSet2;
        }
    }
    //Updating the solution to the new one
    this->solutionMsb.set1 = set1;
    this->solutionMsb.set2 = set2;
    this->solutionMsb.edgesBetween = edgesBetween;
}

//Function to shift a block of 1 (010011100) on the right (the block of one are the three ones next to each other)
void generateSetsRightShift(int myBin, int nbBits, int pos1moving, Graph* G, vector<map<string, int>> restoreMyBin){
    int posFirst0, posLast0;//For left shifting
    // pos1moving bit is a 0 <=> we shift the block of one on the right on one bit
    if (((myBin & (1 << pos1moving)) >> pos1moving) == 0) {
        pos1moving = getMostRight1Pos(myBin);
        //If the block of ones shifting on right reached the bit pos 0
        if (pos1moving == 0){
            return;
        }
    }
    // Else, if we can shift some ones on the left of the block of 1 currently shifting on right
    else if (countZeroOnLeft(myBin, pos1moving, &posFirst0, &posLast0) > 1 ){
        int newNbBits = posLast0 - pos1moving+1;
        int newMyBin = sum2PwrN(0, posFirst0 - 1 - pos1moving);
        int newPos1Moving = posFirst0 - 1 - pos1moving;
        map<string, int> restoreCurrentMyBin;
        restoreCurrentMyBin["pos1moving"] = pos1moving;
        restoreCurrentMyBin["myBin"] = myBin;
        restoreCurrentMyBin["posFirst0"] = posFirst0;
        restoreMyBin.push_back(restoreCurrentMyBin);
        //Shift on the left the block of 1 where is pos1moving untill there is only one 0 between the block we shift and others 1
        generateSetsLeftShift(newMyBin, newNbBits, newPos1Moving, G, restoreMyBin);
        restoreMyBin.pop_back();
    }
    //Shift pos1Moving bit on right
    myBin -= pwr(2, pos1moving-1);
    if (nbBits == G->getVertexList().size()){
        G->isExactSolutionBetter(myBin);
    }
    else{
        int restoredBin = myBin;
        for(int i = restoreMyBin.size()-1; i>= 0;i--){
           restoredBin = (restoredBin << restoreMyBin[i].find("pos1moving")->second) + restoreMyBin[i].find("myBin")->second - sum2PwrN(restoreMyBin[i].find("pos1moving")->second, restoreMyBin[i].find("posFirst0")->second-1);
        }
        G->isExactSolutionBetter(restoredBin);
    }
    generateSetsRightShift(myBin, nbBits, pos1moving+1, G, restoreMyBin);
}


//Function to shift a block of 1 (0000001111110) on the left and find all combinaisons
void generateSetsLeftShift(int myBin, int nbBits, int pos1moving, Graph* G, vector<map<string, int>> restoreMyBin){
    int mostLeft1Pos = getMostLeft1Pos(myBin, nbBits);
    int nbOneInMyBin = nbOne(myBin, nbBits);
    // If there is a block of 1 like (000011111100)
    if (sum2PwrN(mostLeft1Pos- nbOneInMyBin+1, mostLeft1Pos) == myBin){
        pos1moving = mostLeft1Pos;
        // If there is a block of 1 like (011100 nbBits=6)   or myBin =2 and nbBits=2
        if (mostLeft1Pos == nbBits-2 || (myBin == 2 && nbBits == 2)){
            return;
        }
    }
    // Else if myBin is even => we can shift some 1 on the right because there is at least one zero on the rights of all the ones
    else if (myBin%2 == 0) {
        generateSetsRightShift(myBin, nbBits, getMostRight1Pos(myBin), G, restoreMyBin);
    }
    // Shift pos1moving bit on the left
    myBin += pwr(2, pos1moving);
    if (nbBits == G->getVertexList().size()){
        G->isExactSolutionBetter(myBin);
    }
    else{
        // If we are in the case where we went in this function from right_shift function, we have to retrieve the original value of myBin thanks to restoreMyBin vector
        int restoredBin = myBin;
        for(int i = restoreMyBin.size()-1; i>= 0;i--){//O(log(n))
            restoredBin = (restoredBin << restoreMyBin[i].find("pos1moving")->second) + restoreMyBin[i].find("myBin")->second - sum2PwrN(restoreMyBin[i].find("pos1moving")->second, restoreMyBin[i].find("posFirst0")->second-1);
        }
        G->isExactSolutionBetter(restoredBin);
    }
    generateSetsLeftShift(myBin, nbBits, pos1moving-1, G, restoreMyBin);
}


void Graph::exactSolutionMSB(){
    int graphSize = this->getVertexList().size();
    int firstBin2FindSets = pwr(2, (graphSize+1)/2)-1;
    if (graphSize%2 != 0){
        cout << "Error: Graph size must be even" << endl;
        return;
    }
    //Init first vertex sets
    this->solutionMsb.edgesBetween = pwr(graphSize, 2);
    this->isExactSolutionBetter(firstBin2FindSets);
    generateSetsLeftShift(firstBin2FindSets, graphSize,  getMostLeft1Pos(firstBin2FindSets, graphSize), this);
   /* Display solution
    cout << "set1:";
    for (auto v: this->solutionMsb.set1){
        cout << " " << v->getValue();
    }
    cout << endl << "set2:";
    for (auto v: this->solutionMsb.set2){
        cout << " " << v->getValue();
    }
    cout << endl << "number of edges between sets: " << this->solutionMsb.edgesBetween;*/
}