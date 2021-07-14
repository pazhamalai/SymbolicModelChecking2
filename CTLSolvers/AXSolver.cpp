//
// Created by pazhamalai on 10/07/21.
//

#include "AXSolver.h"
#include "FormulaUtils.h"

DdNode *AXSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {

    formula->firstArgument = Formula_Not(formula->firstArgument);
    formula->type = EX;
    DdNode* result = converter->convertFormula(formula, transitionLevel);
    result = Cudd_Not(result);
    Cudd_Ref(result);
    return result;
}
