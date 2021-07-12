#include <iostream>
#include "cudd.h"
#include "Globals/GlobalStorage.h"
#include "MCIP.h"
#include "FormulaToBDDConverter/FormulaToBDDConverter.h"

const char* INPUT_FILE_PATH = "/home/pazhamalai/CLionProjects/SymbolicModelChecking2/test/2/data.txt";

void initBDD() {
    DdManager* manager = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0);
    GlobalStorage::getInstance()->setDdManager(manager);
}

void initInput() {
    FILE* dataFile = fopen(INPUT_FILE_PATH, "r");
    InputInfo* input = readInput(dataFile);
    fclose(dataFile);
    GlobalStorage::getInstance()->setInputInfo(input);
}

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

int main() {
    initBDD();
    initInput();
//    convertCTLFormulaToBDD();
//    dumpBDDAsDotFile();

    FormulaToBDDConverter converter;
    DdNode* ctlBDD = converter.convertFormula(GlobalStorage::getInstance()->CTLFormula, 0);
    Cudd_Ref(ctlBDD);

    ctlBDD = Cudd_BddToAdd(GlobalStorage::getInstance()->ddManager, ctlBDD);
    char fileName[90];
    sprintf(fileName, "/home/pazhamalai/CLionProjects/SymbolicModelChecking2/test/2/graph.dot");
    printf("%s", fileName);
    write_dd(GlobalStorage::getInstance()->ddManager, ctlBDD, fileName);
    Cudd_Quit(GlobalStorage::getInstance()->ddManager);

    return 0;
}