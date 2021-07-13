//
// Created by pazhamalai on 13/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_ERSOLVER_H
#define SYMBOLICMODELCHECKING2_ERSOLVER_H

#include "CTLSolver.h"

class ERSolver : public CTLSolver {
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) override;
};


#endif //SYMBOLICMODELCHECKING2_ERSOLVER_H
