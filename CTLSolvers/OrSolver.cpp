//
// Created by pazhamalai on 13/07/21.
//

#include "OrSolver.h"

DdNode *OrSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    DdNode* firstArgumentBDD = converter->convertFormula(formula->firstArgument, transitionLevel);
    DdNode* secondArgumentBDD = converter->convertFormula(formula->secondArgument, transitionLevel);

    DdNode* result = Cudd_bddOr(GlobalStorage::getInstance()->ddManager, firstArgumentBDD, secondArgumentBDD);
    Cudd_Ref(result);
    return result;
}
