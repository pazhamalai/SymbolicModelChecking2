//
// Created by pazhamalai on 13/07/21.
//

#include "EFSolver.h"
#include "FormulaUtils.h"

// EF f Solved by E(true U f)
DdNode *EFSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    formula->secondArgument = formula->firstArgument;
    formula->firstArgument = Formula_True();
    formula->type = EU;
    return converter->convertFormula(formula, transitionLevel);
}
