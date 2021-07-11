//
// Created by pazhamalai on 08/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_FORMULATOBDDCONVERTER_H
#define SYMBOLICMODELCHECKING2_FORMULATOBDDCONVERTER_H

#include "MCIP.h"

class DdNode;

class FormulaToBDDConverter {
public:
    DdNode* convertFormula(struct Formula* formula, int transitionLevel);
};

#endif //SYMBOLICMODELCHECKING2_FORMULATOBDDCONVERTER_H
