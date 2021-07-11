//
// Created by pazhamalai on 09/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_ANDSOLVER_H
#define SYMBOLICMODELCHECKING2_ANDSOLVER_H

#include "CTLSolver.h"

class AndSolver : public CTLSolver{
public:
    DdNode* solveCTL(Formula* formula, int transitionLevel, FormulaToBDDConverter* converter) override;
};


#endif //SYMBOLICMODELCHECKING2_ANDSOLVER_H
