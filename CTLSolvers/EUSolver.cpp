//
// Created by pazhamalai on 11/07/21.
//

#include "EUSolver.h"
#include "../FixPoints/leastFixPoint.h"
#include "../FormulaToBDDConverter/TransitionRelationToBDDConverter.h"
#include "../Utils/BDDUtils.h"

// The variables are declared here so that the tau function will have only one argument Z.
// And leastFixPoint can be computed with this format in a single place.
DdNode* EU_F1_BDD;
DdNode* EU_F2_BDD;
int EU_transitionLevel;
FormulaToBDDConverter* EU_fBDD_Converter;

DdNode* EU_getEX(DdNode* Z) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;

    // Computes EX (Z)

    // Get TransitionRelation for transitionLevel
    TransitionRelationToBDDConverter transitionConverter;
    DdNode* transitionNode = transitionConverter.getTransitionRelationAsBDD(EU_transitionLevel, EU_fBDD_Converter);

    // Compute Z' where Z' is Z with next state variables
    DdNode* nextStateZ = moveBDDToNextState(Z, EU_transitionLevel);

    // Existential S' (T(s, s') ^ Z')
    DdNode* EXResult = Cudd_bddAndAbstract(manager, transitionNode, nextStateZ, createCubeVariablesBDD(EU_transitionLevel + 1));
    Cudd_Ref(EXResult);
    return EXResult;
}

DdNode* EU_tau(DdNode* Z) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;

    // EX(Z)
    DdNode* EXResult = EU_getEX(Z);

    // f1 ^ EX(Z)
    DdNode* interNode1 = Cudd_bddAnd(manager, EXResult, EU_F1_BDD);

    // f2 \/ (f1 ^ EX(Z))
    DdNode* EUResult = Cudd_bddOr(manager, interNode1, EU_F2_BDD);
    Cudd_Ref(EUResult);
    return EUResult;

}

DdNode *EUSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    EU_F1_BDD = converter->convertFormula(formula->firstArgument, transitionLevel);
    EU_F2_BDD = converter->convertFormula(formula->secondArgument, transitionLevel);
    return leastFixPoint(EU_tau);
}
