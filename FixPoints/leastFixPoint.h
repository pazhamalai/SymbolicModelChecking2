//
// Created by pazhamalai on 11/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_LEASTFIXPOINT_H
#define SYMBOLICMODELCHECKING2_LEASTFIXPOINT_H

class DdNode;

DdNode* leastFixPoint(DdNode* (*tau)(DdNode*));

#endif //SYMBOLICMODELCHECKING2_LEASTFIXPOINT_H
