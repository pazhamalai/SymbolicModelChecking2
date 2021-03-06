//
// Created by pazhamalai on 11/07/21.
//

#include "EUSolver.h"
#include "../FixPoints/leastFixPoint.h"
#include "../FormulaToBDDConverter/TransitionRelationToBDDConverter.h"
#include "../Utils/BDDUtils.h"
#include "FormulaUtils.h"
#include "../BDD_Dumper.h"

int GENERATE_WITNESS = 0;

// The variables are declared here so that the tau function will have only one argument Z.
// And leastFixPoint can be computed with this format in a single place.
DdNode* EU_F1_BDD;
DdNode* EU_F2_BDD;
int EU_transitionLevel;
FormulaToBDDConverter* EU_fBDD_Converter;

EUWitnessGenerator* EU_WitnessGenerator;

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
    EU_WitnessGenerator->addTau(EUResult);
    return EUResult;

}

DdNode *EUSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    EU_F1_BDD = converter->convertFormula(formula->firstArgument, transitionLevel);
    EU_F2_BDD = converter->convertFormula(formula->secondArgument, transitionLevel);

    EU_transitionLevel = transitionLevel;
    EU_WitnessGenerator = &witnessGenerator;
    EU_WitnessGenerator->init();
    EU_WitnessGenerator->setF1BDD(EU_F1_BDD);
    EU_WitnessGenerator->setF2BDD(EU_F2_BDD);

    // If fairness conditions are present, the second argument becomes
    // f2 ^ fair
    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    int numberOfFairnessConstraints = GlobalStorage::getInstance()->numberOfFairnessConstraints;
    if (numberOfFairnessConstraints > 0) {
        DdNode* allFairStates = converter->convertFormula(Formula_EG(Formula_True()), transitionLevel);
        Cudd_Ref(allFairStates);

        EU_F2_BDD = Cudd_bddAnd(manager, EU_F2_BDD, allFairStates);
    }

    DdNode* result =  leastFixPoint(EU_tau);
    Cudd_Ref(result);

    //Witness Generation
    if (numberOfFairnessConstraints == 0 && GENERATE_WITNESS) {
        EU_WitnessGenerator = &witnessGenerator;
        EU_WitnessGenerator->forwardSymbolicSimulation();
    }

    return result;
}
