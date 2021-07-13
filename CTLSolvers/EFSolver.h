//
// Created by pazhamalai on 13/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_EFSOLVER_H
#define SYMBOLICMODELCHECKING2_EFSOLVER_H

#include "CTLSolver.h"

class EFSolver : public CTLSolver{
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) override;
};


#endif //SYMBOLICMODELCHECKING2_EFSOLVER_H
