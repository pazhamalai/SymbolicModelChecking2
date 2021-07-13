//
// Created by pazhamalai on 13/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_EGSOLVER_H
#define SYMBOLICMODELCHECKING2_EGSOLVER_H

#include "CTLSolver.h"

class EGSolver : public CTLSolver{
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) override;
};


#endif //SYMBOLICMODELCHECKING2_EGSOLVER_H
