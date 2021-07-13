//
// Created by pazhamalai on 10/07/21.
//

#include "AXSolver.h"
#include "../FormulaToBDDConverter/TransitionRelationToBDDConverter.h"
#include "../Utils/SMCFormulaUtils.h"

DdNode *AXSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    // BDD for T(s, s')
    TransitionRelationToBDDConverter transitionConverter;
    DdNode* transitionNode = transitionConverter.getTransitionRelationAsBDD(transitionLevel, converter);
    Cudd_Ref(transitionNode);

    // change F(s) to F(s')
    changeVariables(formula->firstArgument, transitionLevel + 1);

    // BDD for ¬F(s')
    DdNode* formulaNode = converter->convertFormula(formula->firstArgument, transitionLevel + 1);
    formulaNode = Cudd_Not(formulaNode);
    Cudd_Ref(formulaNode);

    // BDD for ¬(∃s'(T(s, s') ^ ¬F(s')))
    DdNode* result = Cudd_bddAndAbstract(GlobalStorage::getInstance()->ddManager, transitionNode, formulaNode, formulaNode);
    result = Cudd_Not(result);
    Cudd_Ref(result);
    return result;
}
