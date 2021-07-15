//
// Created by pazhamalai on 09/07/21.
//

#include "EXSolver.h"
#include "../FormulaToBDDConverter/TransitionRelationToBDDConverter.h"
#include "../Utils/BDDUtils.h"
#include "FormulaUtils.h"

DdNode *EXSolver::solveCTL(struct Formula *formula, int transitionLevel, FormulaToBDDConverter* converter) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    int numberOfFairnessConstraints = GlobalStorage::getInstance()->numberOfFairnessConstraints;

    // BDD for T(s, s')
    TransitionRelationToBDDConverter transitionConverter;
    DdNode* transitionNode = transitionConverter.getTransitionRelationAsBDD(transitionLevel, converter);

    // BDD for F(s')
    DdNode* formulaNode = converter->convertFormula(formula->firstArgument, transitionLevel);
    formulaNode = moveBDDToNextState(formulaNode, transitionLevel);
    Cudd_Ref(formulaNode);

    if (numberOfFairnessConstraints > 0) {
        // formulaNode is changed to f1 ^ (EG true)
        DdNode* allFairStates = converter->convertFormula(Formula_EG(Formula_True()), transitionLevel + 1);
        Cudd_Ref(allFairStates);
        formulaNode = Cudd_bddAnd(manager, formulaNode, allFairStates);
        Cudd_Ref(formulaNode);
    }

    // BDD for ∃s'(T(s, s') ^ F(s'))
    DdNode* result = Cudd_bddAndAbstract(GlobalStorage::getInstance()->ddManager, transitionNode, formulaNode,
                                         createCubeVariablesBDD(transitionLevel + 1));
    Cudd_Ref(result);
    return result;
}
