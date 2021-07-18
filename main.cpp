#include <iostream>
#include "cudd.h"
#include "Globals/GlobalStorage.h"
#include "MCIP.h"
#include "FormulaToBDDConverter/FormulaToBDDConverter.h"
#include "BDD_Dumper.h"
#include "cstring"

const char* INPUT_DIRECTORY = "/home/pazhamalai/CLionProjects/SymbolicModelChecking2/test/microwaveOven";
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

void checkCTLHolds(DdNode* ctlBDD) {
    FormulaToBDDConverter converter;
    Formula* initialStates = GlobalStorage::getInstance()->initialStatesFormula;
    DdNode* initialBDD = converter.convertFormula(initialStates, 0);
    DdManager* manager = GlobalStorage::getInstance()->ddManager;
    DdNode* result = Cudd_bddAnd(manager, ctlBDD, initialBDD);
    if (result == Cudd_ReadLogicZero(manager)) {
        printf("Formula does not holds\n");
    } else {
        printf("Formula holds\n");
    }
}

int main() {
    initBDD();
    initInput();
    DdNode* ctlBDD = convertCTLFormula();
    checkCTLHolds(ctlBDD);
    dumpBDDasDot(ctlBDD, DOT_FILE_PATH);
    Cudd_Quit(GlobalStorage::getInstance()->ddManager);
    return 0;
}