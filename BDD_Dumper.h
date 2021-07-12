//
// Created by pazhamalai on 13/07/21.
//

#ifndef SYMBOLICMODELCHECKING2_BDD_DUMPER_H
#define SYMBOLICMODELCHECKING2_BDD_DUMPER_H

#include "iostream"
#include "cudd.h"

void dumpBDDasDot(DdNode* ctlBDD, const char* DotFilePath);

#endif //SYMBOLICMODELCHECKING2_BDD_DUMPER_H
