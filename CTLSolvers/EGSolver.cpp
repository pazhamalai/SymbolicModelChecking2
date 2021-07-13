//
// Created by pazhamalai on 13/07/21.
//

#include "EGSolver.h"
#include "../FormulaToBDDConverter/TransitionRelationToBDDConverter.h"
#include "../Utils/BDDUtils.h"
#include "../FixPoints/greatestFixPoint.h"

DdNode* EG_F1_BDD;
int EG_TransitionLevel;
FormulaToBDDConverter* EG_fBDD_Converter;

DdNode* EG_getEX(DdNode* Z) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;

    // Computes EX (Z)

    // Get TransitionRelation for transitionLevel
    TransitionRelationToBDDConverter transitionConverter;
    DdNode* transitionNode = transitionConverter.getTransitionRelationAsBDD(EG_TransitionLevel, EG_fBDD_Converter);

    // Compute Z' where Z' is Z with next state variables
    DdNode* nextStateZ = moveBDDToNextState(Z, EG_TransitionLevel);

    // Existential S' (T(s, s') ^ Z')
    DdNode* EXResult = Cudd_bddAndAbstract(manager, transitionNode, nextStateZ, createCubeVariablesBDD(EG_TransitionLevel + 1));
    Cudd_Ref(EXResult);
    return EXResult;
}

DdNode* EG_tau(DdNode* Z) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;

    DdNode* EG_EX = EG_getEX(Z);
    Cudd_Ref(EG_EX);

    DdNode* result = Cudd_bddAnd(manager, EG_F1_BDD, EG_EX);
    Cudd_Ref(result);
    return result;
}

DdNode *EGSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    EG_F1_BDD = converter->convertFormula(formula->firstArgument, transitionLevel);
    EG_TransitionLevel = transitionLevel;
    return greatestFixPoint(EG_tau);
}
