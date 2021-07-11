//
// Created by pazhamalai on 09/07/21.
//

#include "FormulaUtils.h"

void changeVariables(Formula* formula, int transitionLevel) {
    if (formula == nullptr)
        return;

    int numberOfVariables = GlobalStorage::getInstance()->numberOfVariables;

    if (formula->variableValue != -1) {
        formula->variableValue = (transitionLevel * numberOfVariables) + (formula->variableValue % numberOfVariables);
    }

    changeVariables(formula->firstArgument, transitionLevel);
    changeVariables(formula->secondArgument, transitionLevel);
}