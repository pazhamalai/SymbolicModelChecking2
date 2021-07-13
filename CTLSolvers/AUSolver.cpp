//
// Created by pazhamalai on 13/07/21.
//

#include "AUSolver.h"
#include "../FormulaToBDDConverter/TransitionRelationToBDDConverter.h"
#include "../Utils/BDDUtils.h"
#include "../FixPoints/leastFixPoint.h"

DdNode* AU_F1_BDD;
DdNode* AU_F2_BDD;
int AU_transitionLevel;
FormulaToBDDConverter* AU_fBDD_Converter;

DdNode* AU_getAX(DdNode* Z) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;

    // Computes AX (Z)

    // Get TransitionRelation for transitionLevel
    TransitionRelationToBDDConverter transitionConverter;
    DdNode* transitionNode = transitionConverter.getTransitionRelationAsBDD(AU_transitionLevel, AU_fBDD_Converter);

    // Compute ¬Z' where Z' is Z with next state variables
    DdNode* nextStateZ = moveBDDToNextState(Z, AU_transitionLevel);
    nextStateZ = Cudd_Not(nextStateZ);

    // Existential S' (T(s, s') ^ ¬Z')
    DdNode* AXResult = Cudd_bddAndAbstract(manager, transitionNode, nextStateZ, createCubeVariablesBDD(AU_transitionLevel + 1));
    AXResult = Cudd_Not(AXResult);
    Cudd_Ref(AXResult);
    return AXResult;
}

DdNode* AU_tau(DdNode* Z) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;

    // AX(Z)
    DdNode* EXResult = AU_getAX(Z);

    // f1 ^ AX(Z)
    DdNode* interNode1 = Cudd_bddAnd(manager, EXResult, AU_F1_BDD);

    // f2 \/ (f1 ^ AX(Z))
    DdNode* EUResult = Cudd_bddOr(manager, interNode1, AU_F2_BDD);
    Cudd_Ref(EUResult);
    return EUResult;

}


DdNode *AUSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    AU_F1_BDD = converter->convertFormula(formula->firstArgument, transitionLevel);
    AU_F2_BDD = converter->convertFormula(formula->secondArgument, transitionLevel);
    AU_transitionLevel = transitionLevel;
    return leastFixPoint(AU_tau);
}
