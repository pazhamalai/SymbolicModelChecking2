//
// Created by pazhamalai on 09/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_VARSOLVERS_H
#define SYMBOLICMODELCHECKING2_VARSOLVERS_H

#include "CTLSolver.h"

class VarSolvers : public CTLSolver {
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter* converter) override;
};


#endif //SYMBOLICMODELCHECKING2_VARSOLVERS_H
