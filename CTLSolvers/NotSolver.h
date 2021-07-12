//
// Created by pazhamalai on 13/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_NOTSOLVER_H
#define SYMBOLICMODELCHECKING2_NOTSOLVER_H

#include "CTLSolver.h"

class NotSolver : public CTLSolver{
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) override;
};


#endif //SYMBOLICMODELCHECKING2_NOTSOLVER_H
