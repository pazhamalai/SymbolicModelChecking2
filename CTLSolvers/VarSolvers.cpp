//
// Created by pazhamalai on 09/07/21.
//

#include "VarSolvers.h"

DdNode *VarSolvers::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter* converter) {
    DdNode* var =  Cudd_bddIthVar(GlobalStorage::getInstance()->ddManager, formula->variableValue);
    Cudd_Ref(var);
    return var;
}
