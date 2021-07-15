//
// Created by pazhamalai on 11/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_EUSOLVER_H
#define SYMBOLICMODELCHECKING2_EUSOLVER_H

#include "CTLSolver.h"
#include "../WitnessGenerator/EUWitnessGenerator.h"

class EUSolver : public CTLSolver{
private:
    EUWitnessGenerator witnessGenerator;
public:
    DdNode * solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) override;
};


#endif //SYMBOLICMODELCHECKING2_EUSOLVER_H
