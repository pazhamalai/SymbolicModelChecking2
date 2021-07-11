//
// Created by pazhamalai on 11/07/21.
//

#include "BDDUtils.h"
#include "../Globals/GlobalStorage.h"
#include "cudd.h"

DdNode* moveBDDToNextState(DdNode* bdd, int currentTransitionLevel) {
    int numberOfVariables = GlobalStorage::getInstance()->numberOfVariables;
    DdManager* manager = GlobalStorage::getInstance()->ddManager;

    DdNode* currentStateVariables[numberOfVariables];
    DdNode* nextStateVariables[numberOfVariables];

    for (int i = 0; i < numberOfVariables; ++i) {
        currentStateVariables[i] = Cudd_bddIthVar(manager, (currentTransitionLevel * numberOfVariables) + (i % numberOfVariables));
        nextStateVariables[i] = Cudd_bddIthVar(manager, ((currentTransitionLevel + 1) * numberOfVariables) + (i % numberOfVariables));
    }

    DdNode* nextStateZ = Cudd_bddSwapVariables(manager, bdd, currentStateVariables, nextStateVariables, numberOfVariables);
    Cudd_Ref(nextStateZ);
    return nextStateZ;
}

DdNode* createCubeVariablesBDD(int transitionLevel) {
    int numberOfVariables = GlobalStorage::getInstance()->numberOfVariables;
    DdManager* manager = GlobalStorage::getInstance()->ddManager;

    DdNode* nextVariablesBDD = Cudd_bddIthVar(manager, transitionLevel * numberOfVariables);
    for (int i = 1; i < numberOfVariables; ++i) {
        nextVariablesBDD = Cudd_bddAnd(manager, nextVariablesBDD, Cudd_bddIthVar(manager, (transitionLevel * numberOfVariables) + (i % numberOfVariables)));
    }

    Cudd_Ref(nextVariablesBDD);
    return nextVariablesBDD;
}
