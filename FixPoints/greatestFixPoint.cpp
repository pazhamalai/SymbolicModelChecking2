//
// Created by pazhamalai on 13/07/21.
//

#include "greatestFixPoint.h"
#include "iostream"
#include "cudd.h"
#include "../Globals/GlobalStorage.h"

DdNode* greatestFixPoint(DdNode* (*tau)(DdNode*)) {
    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    DdNode* Q = Cudd_ReadOne(manager);
    DdNode* Q_Prime = tau(Q);

    while (Q != Q_Prime) {
        Q = Q_Prime;
        Q_Prime = tau(Q);
    }

    return Q;
}
