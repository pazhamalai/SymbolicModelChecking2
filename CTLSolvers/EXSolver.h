//
// Created by pazhamalai on 09/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_EXSOLVER_H
#define SYMBOLICMODELCHECKING2_EXSOLVER_H

#include "CTLSolver.h"


class EXSolver : public CTLSolver {
public:
    DdNode* solveCTL(Formula* formula, int transitionLevel, FormulaToBDDConverter* converter) override;
};


#endif //SYMBOLICMODELCHECKING2_EXSOLVER_H
