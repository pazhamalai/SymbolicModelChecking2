//
// Created by pazhamalai on 13/07/21.
//

#include "BDD_Dumper.h"
#include "Globals/GlobalStorage.h"

void write_dd (DdManager *gbm, DdNode *dd, char* filename)
{
    FILE *outfile; // output file pointer for .dot file
    outfile = fopen(filename,"w");
    auto **ddnodearray = (DdNode**)malloc(sizeof(DdNode*)); // initialize the function array
    ddnodearray[0] = dd;
    Cudd_DumpDot(gbm, 1, ddnodearray, nullptr, nullptr, outfile); // dump the function to .dot file
    free(ddnodearray);
    fclose (outfile); // close the file */
}

void dumpBDDasDot(DdNode* ctlBDD, const char* DotFilePath) {
    ctlBDD = Cudd_BddToAdd(GlobalStorage::getInstance()->ddManager, ctlBDD);
    char fileName[90];
    sprintf(fileName, "%s", DotFilePath);
    printf("%s", fileName);
    write_dd(GlobalStorage::getInstance()->ddManager, ctlBDD, fileName);
}