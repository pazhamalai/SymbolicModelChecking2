//
// Created by pazhamalai on 10/07/21.
//

#include "GlobalStorage.h"

GlobalStorage* GlobalStorage::instance = 0;

GlobalStorage *GlobalStorage::getInstance() {
    if (instance == nullptr)
    {
        instance = new GlobalStorage();
    }

    return instance;
}

void GlobalStorage::setInputInfo(InputInfo *info) {
    transitionFormula = info->transitionFormula;
    initialStatesFormula = info->initialStatesFormula;
    CTLFormula = info->ctlFormula;
    numberOfVariables = info->numberOfVariables;
    variables = info->variables;
    fairnessConstraints = info->fairnessConstraints;
    numberOfFairnessConstraints = info->numberOfFairnessConstraints;
    currentTransitionLevel = 0;
}

void GlobalStorage::setDdManager(DdManager *manager) {
    ddManager = manager;
}
