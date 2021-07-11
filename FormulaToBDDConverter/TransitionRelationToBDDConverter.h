//
// Created by pazhamalai on 10/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_TRANSITIONRELATIONTOBDDCONVERTER_H
#define SYMBOLICMODELCHECKING2_TRANSITIONRELATIONTOBDDCONVERTER_H

#include "FormulaToBDDConverter.h"

struct DdNode;
class FormulaToBDDConverter;

class TransitionRelationToBDDConverter {
public:
    DdNode* getTransitionRelationAsBDD(int transitionLevel, FormulaToBDDConverter* converter);
};


#endif //SYMBOLICMODELCHECKING2_TRANSITIONRELATIONTOBDDCONVERTER_H
