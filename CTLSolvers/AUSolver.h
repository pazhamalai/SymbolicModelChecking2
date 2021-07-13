//
// Created by pazhamalai on 13/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_AUSOLVER_H
#define SYMBOLICMODELCHECKING2_AUSOLVER_H

#include "CTLSolver.h"

class AUSolver : public CTLSolver{
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) override;
};


#endif //SYMBOLICMODELCHECKING2_AUSOLVER_H
