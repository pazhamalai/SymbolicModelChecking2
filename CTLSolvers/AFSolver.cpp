//
// Created by pazhamalai on 13/07/21.
//

#include "AFSolver.h"

extern "C" {
#include "FormulaUtils.h"
}
// AF f solved by (Not (EG (Not f)))
DdNode *AFSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    formula->type = EG;
    formula->firstArgument = Formula_Not(formula->firstArgument);
    DdNode* result = converter->convertFormula(formula, transitionLevel);
    result = Cudd_Not(result);
    Cudd_Ref(result);
    return result;
}
