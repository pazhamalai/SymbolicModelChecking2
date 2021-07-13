#include <iostream>
#include "cudd.h"
#include "Globals/GlobalStorage.h"
#include "MCIP.h"
#include "FormulaToBDDConverter/FormulaToBDDConverter.h"
#include "BDD_Dumper.h"
#include "cstring"

const char* INPUT_DIRECTORY = "/home/pazhamalai/CLionProjects/SymbolicModelChecking2/test/2";
char INPUT_FILE_PATH[255];
char DOT_FILE_PATH[255];

void initBDD() {
    DdManager* manager = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0);
    GlobalStorage::getInstance()->setDdManager(manager);
}

void setInputDirectory() {
    strcat(INPUT_FILE_PATH, INPUT_DIRECTORY);
    strcat(INPUT_FILE_PATH, "/data.txt");
}

void setDotFileDirectory() {
    strcat(DOT_FILE_PATH, INPUT_DIRECTORY);
    strcat(DOT_FILE_PATH, "/graph.dot");
}

void initInput() {
    setInputDirectory();
    setDotFileDirectory();

    FILE* dataFile = fopen(INPUT_FILE_PATH, "r");
    InputInfo* input = readInput(dataFile);
    fclose(dataFile);
    GlobalStorage::getInstance()->setInputInfo(input);
}

DdNode* convertCTLFormula() {
    FormulaToBDDConverter converter;
    DdNode* ctlBDD = converter.convertFormula(GlobalStorage::getInstance()->CTLFormula, 0);
    Cudd_Ref(ctlBDD);
    return ctlBDD;
}

int main() {
    initBDD();
    initInput();
    DdNode* ctlBDD = convertCTLFormula();
    dumpBDDasDot(ctlBDD, DOT_FILE_PATH);

    // EF f can be computed as E (true U f)
    // AF can be computed in-terms of EG.
    // AR f can be computed as Not. E ( Nf1 U Nf2)
    return 0;
}