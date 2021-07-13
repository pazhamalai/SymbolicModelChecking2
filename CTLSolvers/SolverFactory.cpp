//
// Created by pazhamalai on 09/07/21.
//

#include "SolverFactory.h"

#include "EXSolver.h"
#include "AXSolver.h"

#include "EUSolver.h"
#include "AUSolver.h"

#include "EFSolver.h"
#include "AFSolver.h"

#include "EGSolver.h"
#include "AGSolver.h"

#include "ERSolver.h"
#include "ARSolver.h"

#include "AndSolver.h"
#include "OrSolver.h"
#include "NotSolver.h"
#include "VarSolvers.h"
#include "BooleanSolver.h"

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
        case AU:
            solver = new AUSolver();
            break;

        case EF:
            solver = new EFSolver();
            break;
        case AF:
            solver = new AFSolver();
            break;

        case EG:
            solver = new EGSolver();
            break;
        case AG:
            solver = new AGSolver();
            break;

        case ER:
            solver = new ARSolver();
            break;
        case AR:
            solver = new ERSolver();
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

        case BOOLEAN_TRUE:
        case BOOLEAN_FALSE:
            solver = new BooleanSolver();
            break;

        default:
            solver = nullptr;
    }

    return solver;
}
