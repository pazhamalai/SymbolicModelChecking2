//
// Created by pazhamalai on 09/07/21.
//

#include "AndSolver.h"


DdNode *AndSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter* converter) {
    DdNode* firstArgumentBDD = converter->convertFormula(formula->firstArgument, transitionLevel);
    DdNode* secondArgumentBDD = converter->convertFormula(formula->secondArgument, transitionLevel);

    DdNode* result = Cudd_bddAnd(GlobalStorage::getInstance()->ddManager, firstArgumentBDD, secondArgumentBDD);
    Cudd_Ref(result);
    return result;
}
