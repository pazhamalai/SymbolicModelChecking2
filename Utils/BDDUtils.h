//
// Created by pazhamalai on 11/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_BDDUTILS_H
#define SYMBOLICMODELCHECKING2_BDDUTILS_H

class DdNode;

DdNode* moveBDDToNextState(DdNode* bdd, int currentTransitionLevel);

// Creates a dummy BDD with all variables at transitionLevel
// Useful for functions Cudd_bddSwapVariables
DdNode* createCubeVariablesBDD(int transitionLevel);

#endif //SYMBOLICMODELCHECKING2_BDDUTILS_H
