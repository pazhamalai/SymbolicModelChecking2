//
// Created by pazhamalai on 10/07/21.
//

#include "TransitionRelationToBDDConverter.h"
#include "../Globals/GlobalStorage.h"

int isCurrentStateVariable(int varValue, int currentTransitionLevel, int numberOfVariables) {
    int startValue = currentTransitionLevel * numberOfVariables;
    return varValue >= startValue && varValue < (startValue + numberOfVariables);
}

void changeTransitionRelationVariables(Formula* formula, int currentTransitionLevel, int transitionLevel, int numberOfVariables) {
    if (formula == nullptr)
        return;

    int varValue = formula->variableValue;

    if (varValue != -1) {
        if (isCurrentStateVariable(varValue, currentTransitionLevel, numberOfVariables)){
            //Belongs to current state variable
            formula->variableValue = (transitionLevel * numberOfVariables) + (varValue % numberOfVariables);
        }
        else {
            //Belongs to next state
            formula->variableValue = ((transitionLevel + 1) * numberOfVariables) + (varValue % numberOfVariables);
        }
    }

    changeTransitionRelationVariables(formula->firstArgument, currentTransitionLevel, transitionLevel, numberOfVariables);
    changeTransitionRelationVariables(formula->secondArgument, currentTransitionLevel, transitionLevel, numberOfVariables);
}

DdNode *TransitionRelationToBDDConverter::getTransitionRelationAsBDD(int transitionLevel, FormulaToBDDConverter *converter) {
    GlobalStorage* instance = GlobalStorage::getInstance();
    Formula* trFormula = instance->transitionFormula;
    int currentTransitionLevel = instance->currentTransitionLevel;
    if (transitionLevel != currentTransitionLevel)
    {
        changeTransitionRelationVariables(trFormula,
                                          currentTransitionLevel,
                                          transitionLevel,
                                          instance->numberOfVariables);
        instance->currentTransitionLevel = transitionLevel;
    }

    return converter->convertFormula(trFormula, transitionLevel);
}
