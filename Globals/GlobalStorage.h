//
// Created by pazhamalai on 10/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_GLOBALSTORAGE_H
#define SYMBOLICMODELCHECKING2_GLOBALSTORAGE_H

#include "MCIP.h"

class DdManager;

class GlobalStorage
{
private:
    /* Here will be the instance stored. */
    static GlobalStorage* instance;

    /* Private constructor to prevent instancing. */
    GlobalStorage(){
        instance = nullptr;
    }

public:
    DdManager* ddManager;
    Formula* transitionFormula;
    Formula* initialStatesFormula;
    Formula* CTLFormula;
    Formula** fairnessConstraints;
    char** variables;
    int numberOfVariables;
    int currentTransitionLevel;
    int numberOfFairnessConstraints;

    /* Static access method. */
    static GlobalStorage* getInstance();
    void setDdManager(DdManager* manager);
    void setInputInfo(InputInfo* info);
};



#endif //SYMBOLICMODELCHECKING2_GLOBALSTORAGE_H
