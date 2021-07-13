//
// Created by pazhamalai on 13/07/21.
//

#include "EFSolver.h"
#include "cstdlib"

Formula* getTrueFormulaNode() {
    auto* trueNode = (struct Formula*) malloc(sizeof(struct Formula));
    trueNode->type = BOOLEAN_TRUE;
    trueNode->firstArgument = nullptr;
    trueNode->secondArgument = nullptr;
    trueNode->variableValue = -1;
    return trueNode;
}

// EF f Solved by E(true U f)
DdNode *EFSolver::solveCTL(Formula *formula, int transitionLevel, FormulaToBDDConverter *converter) {
    formula->secondArgument = formula->firstArgument;
    formula->firstArgument = getTrueFormulaNode();
    formula->type = EU;
    return converter->convertFormula(formula, transitionLevel);
}
