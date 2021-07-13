//
// Created by pazhamalai on 13/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_AFSOLVER_H
#define SYMBOLICMODELCHECKING2_AFSOLVER_H

#include "CTLSolver.h"

class AFSolver : public CTLSolver{
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) override;
};


#endif //SYMBOLICMODELCHECKING2_AFSOLVER_H
