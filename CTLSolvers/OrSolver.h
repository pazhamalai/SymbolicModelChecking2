//
// Created by pazhamalai on 13/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_ORSOLVER_H
#define SYMBOLICMODELCHECKING2_ORSOLVER_H

#include "CTLSolver.h"

class OrSolver : public CTLSolver{
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) override;
};


#endif //SYMBOLICMODELCHECKING2_ORSOLVER_H
