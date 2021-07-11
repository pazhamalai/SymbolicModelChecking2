//
// Created by pazhamalai on 08/07/21.
//

#include "FormulaToBDDConverter.h"
#include "../CTLSolvers/SolverFactory.h"
#include "cstdlib"

DdNode *FormulaToBDDConverter::convertFormula(struct Formula *formula, int transitionLevel) {
    CTLSolver* solver = getSolverForType(formula->type);
    DdNode* formulaBDD = solver->solveCTL(formula, transitionLevel, this);
    free(solver);
    return formulaBDD;
}
