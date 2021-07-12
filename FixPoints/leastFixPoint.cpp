//
// Created by pazhamalai on 11/07/21.
//

#include "leastFixPoint.h"
#include "iostream"
#include "cstdio"
#include "cstdlib"
#include "cudd.h"
#include "../Globals/GlobalStorage.h"

DdNode* leastFixPoint(DdNode* (*tau)(DdNode*)) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    DdNode* Q = Cudd_ReadLogicZero(manager);
    DdNode* Q_Prime = tau(Q);

    while (Q != Q_Prime) {
        Q = Q_Prime;
        Q_Prime = tau(Q);
    }

    return Q;
}
