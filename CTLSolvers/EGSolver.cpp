//
// Created by pazhamalai on 13/07/21.
//

#include "EGSolver.h"
#include "../FormulaToBDDConverter/TransitionRelationToBDDConverter.h"
#include "../Utils/BDDUtils.h"
#include "../FixPoints/greatestFixPoint.h"
#include "../FixPoints/leastFixPoint.h"

DdNode* EG_F1_BDD;
int EG_TransitionLevel;
FormulaToBDDConverter* EG_fBDD_Converter;


DdNode* EG_EU_F1_BDD;
DdNode* EG_EU_F2_BDD;

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


// Following two functions are for fairness

DdNode* EG_EU_tau(DdNode* Z) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;

    // EX(Z)
    DdNode* EXResult = EG_getEX(Z);

    // f1 ^ EX(Z)
    DdNode* interNode1 = Cudd_bddAnd(manager, EXResult, EG_EU_F1_BDD);

    // f2 \/ (f1 ^ EX(Z))
    DdNode* EUResult = Cudd_bddOr(manager, interNode1, EG_EU_F2_BDD);
    Cudd_Ref(EUResult);
    return EUResult;

}

DdNode* EG_tau_fairness(DdNode* Z) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;

    //Compute BDD of fairness Constraints
    int numberOfFairness = GlobalStorage::getInstance()->numberOfFairnessConstraints;
    Formula** fairnessConstraints = GlobalStorage::getInstance()->fairnessConstraints;

    DdNode* fairnessBDDs[numberOfFairness];
    for (int i = 0; i < numberOfFairness; ++i) {
        fairnessBDDs[i] = EG_fBDD_Converter->convertFormula(fairnessConstraints[i], EG_TransitionLevel);
        Cudd_Ref(fairnessBDDs[i]);
    }

    // Compute from 1 to n, and of, EX (EU (f1) (Z ^ fairness[i]))
    DdNode* prevResult = Cudd_ReadOne(manager);
    DdNode* result;
    EG_EU_F1_BDD = EG_F1_BDD;
    Cudd_Ref(EG_F1_BDD);
    int i = 0;
    while (i < numberOfFairness) {
        DdNode* EUSecond = Cudd_bddAnd(manager, Z, fairnessBDDs[i]);
        EG_EU_F2_BDD = EUSecond;
        Cudd_Ref(EUSecond);
        DdNode* EUResult = leastFixPoint(EG_EU_tau);
        Cudd_Ref(EUResult);
        DdNode* EXResult = EG_getEX(EUResult);
        Cudd_Ref(EXResult);
        result = Cudd_bddAnd(manager, prevResult, EXResult);
        Cudd_Ref(result);
        prevResult = EXResult;
        ++i;
    }

    result = Cudd_bddAnd(manager, EG_F1_BDD, result);
    Cudd_Ref(result);
    return result;
}

DdNode *EGSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    // EfG f
    // Fairness constraints P1 ... Pk
    // F1 ^ ^ (1..n) EX (EU (f) (Z ^ Pi))

    EG_F1_BDD = converter->convertFormula(formula->firstArgument, transitionLevel);
    EG_TransitionLevel = transitionLevel;

    int numberOfFairness = GlobalStorage::getInstance()->numberOfFairnessConstraints;

    if (numberOfFairness > 0)
        return greatestFixPoint(EG_tau_fairness);

    return greatestFixPoint(EG_tau);
}
