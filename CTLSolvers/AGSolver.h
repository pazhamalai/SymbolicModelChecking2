//
// Created by pazhamalai on 13/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_AGSOLVER_H
#define SYMBOLICMODELCHECKING2_AGSOLVER_H

#include "CTLSolver.h"

class AGSolver : public CTLSolver{
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) override;
};


#endif //SYMBOLICMODELCHECKING2_AGSOLVER_H
