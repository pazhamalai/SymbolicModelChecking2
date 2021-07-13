//
// Created by pazhamalai on 13/07/21.
//

#include "ARSolver.h"

extern "C" {
#include "FormulaUtils.h"
}

DdNode *ARSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    formula->type = EU;
    formula->firstArgument = Formula_Not(formula->firstArgument);
    formula->secondArgument = Formula_Not(formula->secondArgument);

    DdNode* result = converter->convertFormula(formula, transitionLevel);
    result = Cudd_Not(result);
    Cudd_Ref(result);
    return result;
}
