

//
// Created by pazhamalai on 10/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_AXSOLVER_H
#define SYMBOLICMODELCHECKING2_AXSOLVER_H

#include "CTLSolver.h"

class AXSolver : public CTLSolver{
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) override;
};


#endif //SYMBOLICMODELCHECKING2_AXSOLVER_H
