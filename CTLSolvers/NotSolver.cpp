//
// Created by pazhamalai on 13/07/21.
//

#include "NotSolver.h"

DdNode *NotSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    DdNode* firstArgumentBDD = converter->convertFormula(formula->firstArgument, transitionLevel);

    DdNode* result = Cudd_Not(firstArgumentBDD);
    Cudd_Ref(result);
    return result;
}
