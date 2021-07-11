//
// Created by pazhamalai on 09/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_SOLVERFACTORY_H
#define SYMBOLICMODELCHECKING2_SOLVERFACTORY_H

#include "MCIP.h"
#include "CTLSolver.h"

class CTLSolver;

CTLSolver* getSolverForType(NodeType type);

#endif //SYMBOLICMODELCHECKING2_SOLVERFACTORY_H
