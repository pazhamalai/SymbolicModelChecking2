//
// Created by pazhamalai on 09/07/21.
//

#include "SolverFactory.h"
#include "EXSolver.h"
#include "AXSolver.h"
#include "AndSolver.h"
#include "OrSolver.h"
#include "NotSolver.h"
#include "VarSolvers.h"
#include "EUSolver.h"

CTLSolver *getSolverForType(NodeType type) {
    CTLSolver* solver;
    switch (type) {
        case EX:
            solver = new EXSolver();
            break;

        case AX:
            solver = new AXSolver();
            break;

        case EU:
            solver = new EUSolver();
            break;

        case AND:
            solver = new AndSolver();
            break;

        case OR:
            solver = new OrSolver();
            break;

        case NOT:
            solver = new NotSolver();
            break;

        case VAR:
            solver = new VarSolvers();
            break;

        default:
            solver = nullptr;
    }

    return solver;
}
