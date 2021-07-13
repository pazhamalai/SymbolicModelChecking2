//
// Created by pazhamalai on 13/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_ARSOLVER_H
#define SYMBOLICMODELCHECKING2_ARSOLVER_H

#include "CTLSolver.h"

class ARSolver : public CTLSolver{
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) override;
};


#endif //SYMBOLICMODELCHECKING2_ARSOLVER_H
