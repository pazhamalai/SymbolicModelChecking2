//
// Created by pazhamalai on 13/07/21.
//

#include "AUSolver.h"
#include "FormulaUtils.h"

DdNode *AUSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    // Solve with EU and EG.
    Formula* f = formula->firstArgument;
    Formula* g = formula->secondArgument;

    Formula* notF = Formula_Not(f);
    Formula* notG = Formula_Not(g);

    Formula* notFAndnotG = Formula_And(notF, notG);

    formula->firstArgument = notG;
    formula->secondArgument = notFAndnotG;
    formula->type = EU;

    DdNode* EUResult = converter->convertFormula(formula, transitionLevel);
    EUResult = Cudd_Not(EUResult);
    Cudd_Ref(EUResult);

    formula->firstArgument = notG;
    formula->secondArgument = nullptr;
    formula->type = EG;

    DdNode* EGResult = converter->convertFormula(formula, transitionLevel);
    EGResult = Cudd_Not(EGResult);
    Cudd_Ref(EGResult);

    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    DdNode* result = Cudd_bddAnd(manager, EUResult, EGResult);
    Cudd_Ref(result);
    return result;
}
