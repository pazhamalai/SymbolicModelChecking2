//
// Created by pazhamalai on 13/07/21.
//

#include "BooleanSolver.h"
#include "iostream"
#include "cudd.h"

DdNode *BooleanSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    if (formula->type == BOOLEAN_TRUE) {
        return Cudd_ReadOne(manager);
    }

    return Cudd_ReadLogicZero(manager);
}
