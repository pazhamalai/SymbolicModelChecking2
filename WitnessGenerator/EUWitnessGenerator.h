//
// Created by pazhamalai on 15/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_EUWITNESSGENERATOR_H
#define SYMBOLICMODELCHECKING2_EUWITNESSGENERATOR_H

#include "iostream"
#include "cudd.h"
#include "../Globals/GlobalStorage.h"

class EUWitnessGenerator {
private:
    DdNode** tauBDDs = nullptr;
    int numberOfTauIterations = 0;
    DdNode* f1BDD;
    DdNode* f2BDD;
    int numberOfVariables;
    int* solution;
    DdNode* solutionBDD;

    void printSolution();
    void findSolutionInBDD(DdNode* bdd);
    void computeInitialSolution();
    void computeNextSolution();
    void storeSolution(const int* assign);
    void computeSolutionBDD();
    DdNode* getImageBDD();
    int solutionSolvesF2();
    int isUnsatBDD(DdNode* bdd);
public:
    EUWitnessGenerator(){
        f1BDD = nullptr;
        f2BDD = nullptr;
        numberOfVariables = 0;
        solution = nullptr;
        solutionBDD = nullptr;
    }
    void init();
    void setF1BDD(DdNode* f1);
    void setF2BDD(DdNode* f2);
    void addTau(DdNode* tau);
    void forwardSymbolicSimulation();
};


#endif //SYMBOLICMODELCHECKING2_EUWITNESSGENERATOR_H
