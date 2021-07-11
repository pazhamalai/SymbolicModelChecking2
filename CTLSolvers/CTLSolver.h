//
// Created by pazhamalai on 08/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_CTLSOLVER_H
#define SYMBOLICMODELCHECKING2_CTLSOLVER_H

#include "MCIP.h"
#include "../Globals/GlobalStorage.h"
#include "cudd.h"
#include "../FormulaToBDDConverter/FormulaToBDDConverter.h"

class DdNode;

class FormulaToBDDConverter;

class CTLSolver {
public:
    virtual DdNode* solveCTL(Formula* formula, int transitionLevel, FormulaToBDDConverter* converter) = 0;
};


#endif //SYMBOLICMODELCHECKING2_CTLSOLVER_H
