#include "src/model/Graph_class/Graph.h"
#include "src/method/exact/exact.h"

//Function to calculate average time of execution of algorithms solving MSB problem depending on different parameters
void test(void (Graph::*pF)(), int nbVerticesMax, int nbInstances2Run4EachTest){
    //Random stuffes
    std::random_device myRandomSeed;
    std::default_random_engine myRandomEngine(myRandomSeed());
    std::uniform_int_distribution<int> myUniformDist(1, 100);
    // Define variables in tests
    vector<char> mode = {'l', 'm'};
    vector<int> proba = {25, 50, 75};
    vector<int> nbVertices;
    vector<int> execTimeM25, execTimeM50, execTimeM75, execTimeL25, execTimeL50, execTimeL75;
    for (int i = 2;i<=nbVerticesMax;i+=2){
        nbVertices.push_back(i);
    }
    for (int n: nbVertices){
        for(int prob: proba){
            for (char mod: mode){
                int avgTime = 0;
                for (int i = 0; i<nbInstances2Run4EachTest;i++){
                    Graph G(n, mod);
                    for (int j = 0; j< G.getVertexList().size();j++){
                        for (int k = j+1; k< G.getVertexList().size();k++){
                            if (myUniformDist(myRandomEngine) <= prob){
                                G.addEdge(G.getVertexList()[j]->getValue(), G.getVertexList()[k]->getValue());
                            }
                        }
                    }
                    auto beginTime = chrono::high_resolution_clock::now();
                    (G.*pF)();
                    auto endTime = chrono::high_resolution_clock::now();
                    int timeElapsed = chrono::duration_cast<chrono::microseconds>(endTime-beginTime).count();
                    avgTime += timeElapsed;
                }
                avgTime /= nbInstances2Run4EachTest;
                if (prob == 25){
                    switch (mod) {
                        case 'l':
                            execTimeL25.push_back(avgTime);
                            break;
                        case 'm':
                            execTimeM25.push_back(avgTime);
                            break;
                    }
                }
                else if (prob == 50){
                    switch (mod) {
                        case 'l':
                            execTimeL50.push_back(avgTime);
                            break;
                        case 'm':
                            execTimeM50.push_back(avgTime);
                            break;
                    }
                }
                else{
                    switch (mod) {
                        case 'l':
                            execTimeL75.push_back(avgTime);
                            break;
                        case 'm':
                            execTimeM75.push_back(avgTime);
                            break;
                    }
                }
            }
        }
    }
    cout << "List of execution time:" << endl;
    cout << "proba = 25:" <<endl;
    cout << "mode = m:" << endl;
    cout << "[ " << execTimeM25[0];
    for (int i = 1; i<execTimeM25.size();i++){
        cout << ", " <<execTimeM25[i];
    }
    cout << "]" << endl;
    cout << "mode = l:" << endl;
    cout << "[ " << execTimeL25[0];
    for (int i = 1; i<execTimeL25.size();i++){
        cout << ", " <<execTimeL25[i];
    }
    cout << "]" << endl;

    cout << "proba = 50:" <<endl;
    cout << "mode = m:" << endl;
    cout << "[ " << execTimeM50[0];
    for (int i = 1; i<execTimeM50.size();i++){
        cout << ", " <<execTimeM50[i];
    }
    cout << "]" << endl;
    cout << "mode = l:" << endl;
    cout << "[ " << execTimeL50[0];
    for (int i = 1; i<execTimeL50.size();i++){
        cout << ", " <<execTimeL50[i];
    }
    cout << "]" << endl;

    cout << "proba = 75:" <<endl;
    cout << "mode = m:" << endl;
    cout << "[ " << execTimeM75[0];
    for (int i = 1; i<execTimeM75.size();i++){
        cout << ", " <<execTimeM75[i];
    }
    cout << "]" << endl;
    cout << "mode = l:" << endl;
    cout << "[ " << execTimeL75[0];
    for (int i = 1; i<execTimeL75.size();i++){
        cout << ", " <<execTimeL75[i];
    }
    cout << "]" << endl;

}

void buildGraphFromFile(string filePath, Graph* G){
    ifstream myFile(filePath);
    string buffStr, buffStr2;
    int nbVertices, nbEdges;
    myFile >> buffStr;
    nbVertices = stoi(buffStr);
    for (int i = 0;i< nbVertices;i++){
        G->addVertex();
    }
    myFile >> buffStr;
    nbEdges = stoi(buffStr);
    for (int i = 0; i< nbEdges;i++) {
        myFile >> buffStr;
        myFile >> buffStr2;
        G->addEdge(stoi(buffStr), stoi(buffStr2));
    }
    myFile.close();
}

void solution2File(string fileName, Graph* G){
    ofstream myFile(fileName);
    myFile << G->getVertexList().size() << " " << G->getSolutionMDB().edgesBetween << endl;
    for (Vertex* v: G->getSolutionMDB().set1){
        myFile << v->getValue() << " ";
    }
    myFile << endl;
    for (Vertex* v: G->getSolutionMDB().set2){
        myFile << v->getValue() << " ";
    }
    myFile.close();
}

int main() {
    string fileName;
    int user_input;
    char modeOfGraph;
    cout << "Representation of th graph:\n\t1- Matrix\n\t2- Adjacency lists\n>> ";
    cin >> user_input;
    if (user_input == 1){
        modeOfGraph = 'm';
    }
    else if (user_input == 2){
        modeOfGraph = 'l';
    }
    else{
        cout << "Wrong user input, leaving the program.";
        return 1;
    }
    Graph G(modeOfGraph);
    cout << "Path to the file to read graph's informations: ";
    cin >> fileName;
    buildGraphFromFile(fileName+".in", &G);
    G.exactSolutionMSB();
    solution2File(fileName+"_exact.out", &G);
    G.constructiveHeuristic();
    solution2File(fileName+"_constructive.out", &G);
    G.localSearchHeuristic();
    solution2File(fileName+"_local_search.out", &G);
    G.tabuSearchHeuristic();
    solution2File(fileName+"_tabu_search.out", &G);
    return 0;
}
