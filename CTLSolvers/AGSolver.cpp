//
// Created by pazhamalai on 13/07/21.
//

#include "AGSolver.h"
#include "FormulaUtils.h"

DdNode *AGSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    formula->type = EF;
    formula->firstArgument = Formula_Not(formula->firstArgument);
    DdNode* result = converter->convertFormula(formula, transitionLevel);
    result = Cudd_Not(result);
    Cudd_Ref(result);
    return result;
}
