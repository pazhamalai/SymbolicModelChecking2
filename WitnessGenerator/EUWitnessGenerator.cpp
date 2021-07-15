//
// Created by pazhamalai on 15/07/21.
//

#include "EUWitnessGenerator.h"
#include "../FormulaToBDDConverter/FormulaToBDDConverter.h"
#include "../Utils/BDDUtils.h"
#include "../FormulaToBDDConverter/TransitionRelationToBDDConverter.h"

void EUWitnessGenerator::addTau(DdNode *tau) {
    Cudd_Ref(tau);

    if (tauBDDs == nullptr)
    {
        tauBDDs = (DdNode**) malloc(sizeof(DdNode*));
        tauBDDs[0] = tau;
        ++numberOfTauIterations;
        return;
    }


    ++numberOfTauIterations;
    tauBDDs = (DdNode**) realloc(tauBDDs, (sizeof(DdNode*)) * numberOfTauIterations);
    tauBDDs[numberOfTauIterations - 1] = tau;
}

void EUWitnessGenerator::forwardSymbolicSimulation() {
    // Last tau will be added twice.
    --numberOfTauIterations;

    if (isUnsatBDD(tauBDDs[0])) {
        //EU has no solution at all.
        return;
    }

    computeInitialSolution();
    while (!solutionSolvesF2()) {
        computeNextSolution();
    }
}

void EUWitnessGenerator::setF1BDD(DdNode *f1) {
    f1BDD = f1;
}

void EUWitnessGenerator::setF2BDD(DdNode *f2) {
    f2BDD = f2;
}

void EUWitnessGenerator::init() {
    numberOfVariables = GlobalStorage::getInstance()->numberOfVariables;
    solution = (int *) malloc(sizeof(int) * numberOfVariables);
}

DdNode* initialStateBDD() {
    FormulaToBDDConverter converter;
    return converter.convertFormula(GlobalStorage::getInstance()->initialStatesFormula, 0);
}

void EUWitnessGenerator::computeInitialSolution() {
    DdNode* tau = tauBDDs[numberOfTauIterations - 1];
    DdNode* initialStates = initialStateBDD();

    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    DdNode* tauAndInit = Cudd_bddAnd(manager, tau, initialStates);
    findSolutionInBDD(tauAndInit);
    --numberOfTauIterations;
}

void EUWitnessGenerator::computeNextSolution() {
    DdNode* imageBDD = getImageBDD();
    DdNode* tauBDD = tauBDDs[numberOfTauIterations - 1];

    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    DdNode* imageAndTau = Cudd_bddAnd(manager, imageBDD, tauBDD);
    findSolutionInBDD(imageAndTau);
    --numberOfTauIterations;
}

void EUWitnessGenerator::findSolutionInBDD(DdNode* bdd) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;

    int* assign;
    CUDD_VALUE_TYPE val;
    DdGen* iter = Cudd_FirstCube(manager, bdd, &assign, &val);
    storeSolution(assign);
    computeSolutionBDD();
    printSolution();
    Cudd_GenFree(iter);
}

void EUWitnessGenerator::storeSolution(const int *assign) {
    for (int i = 0; i < numberOfVariables; ++i) {
        if (assign[i] == 2)
            solution[i] = 0;
        else
            solution[i] = assign[i];
    }
}

DdNode* getVariableBDD(int varIndex, int varValue) {
    DdManager*  manager = GlobalStorage::getInstance()->ddManager;
    DdNode* varNode = Cudd_bddIthVar(manager, varIndex);

    if (!varValue)
        varNode = Cudd_Not(varNode);

    Cudd_Ref(varNode);
    return varNode;
}

void EUWitnessGenerator::computeSolutionBDD() {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    DdNode* result = Cudd_ReadOne(manager);

    for (int i = 0; i < numberOfVariables; ++i) {
        result = Cudd_bddAnd(manager, result, getVariableBDD(i, solution[i]));
    }

    Cudd_Ref(result);
    solutionBDD = result;
}

void EUWitnessGenerator::printSolution() {
    printf("\n");
    for (int i = 0; i < numberOfVariables; ++i) {
        printf("%d", solution[i]);
    }

    printf("\n");
}

DdNode *EUWitnessGenerator::getImageBDD() {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    TransitionRelationToBDDConverter transitionConverter;
    FormulaToBDDConverter formulaConverter;
    DdNode* transitionBDD = transitionConverter.getTransitionRelationAsBDD(0, &formulaConverter);
    Cudd_Ref(transitionBDD);

    DdNode* result = Cudd_bddAndAbstract(manager, solutionBDD, transitionBDD, createCubeVariablesBDD(0));
    DdNode** levelZeroVariables = getVariablesOfLevel(0);
    DdNode** levelOneVariables = getVariablesOfLevel(1);
    result = Cudd_bddSwapVariables(manager,result,levelOneVariables,levelZeroVariables,numberOfVariables);
    Cudd_Ref(result);
    free(levelZeroVariables);
    free(levelOneVariables);
    return result;
}

int EUWitnessGenerator::solutionSolvesF2() {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    DdNode* result = Cudd_bddAnd(manager, solutionBDD, f2BDD);
    Cudd_Ref(result);

    return !isUnsatBDD(result);
}

int EUWitnessGenerator::isUnsatBDD(DdNode *bdd) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    DdNode* unsatBDD = Cudd_ReadLogicZero(manager);

    return bdd == unsatBDD;
}



