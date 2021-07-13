//
// Created by pazhamalai on 13/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_BOOLEANSOLVER_H
#define SYMBOLICMODELCHECKING2_BOOLEANSOLVER_H

#include "CTLSolver.h"

class BooleanSolver : public CTLSolver{
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) override;
};


#endif //SYMBOLICMODELCHECKING2_BOOLEANSOLVER_H
