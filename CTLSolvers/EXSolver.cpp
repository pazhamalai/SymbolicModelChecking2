//
// Created by pazhamalai on 09/07/21.
//

#include "EXSolver.h"
#include "../FormulaToBDDConverter/TransitionRelationToBDDConverter.h"
#include "../Utils/SMCFormulaUtils.h"

DdNode *EXSolver::solveCTL(struct Formula *formula, int transitionLevel, FormulaToBDDConverter* converter) {
    // BDD for T(s, s')
    TransitionRelationToBDDConverter transitionConverter;
    DdNode* transitionNode = transitionConverter.getTransitionRelationAsBDD(transitionLevel, converter);

    // change F(s) to F(s')
    changeVariables(formula->firstArgument, transitionLevel + 1);

    // BDD for F(s')
    DdNode* formulaNode = converter->convertFormula(formula->firstArgument, transitionLevel + 1);

    // BDD for ∃s'(T(s, s') ^ F(s'))
    //TODO This one is wrong. Formula node might not contain all the next state variables.
    // TODO Some missing in them might be present in the transitionNode.
    DdNode* result = Cudd_bddAndAbstract(GlobalStorage::getInstance()->ddManager, transitionNode, formulaNode, formulaNode);
    Cudd_Ref(result);
    return result;
}
