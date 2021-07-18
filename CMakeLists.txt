cmake_minimum_required(VERSION 3.19)
project(SymbolicModelChecking2)

set(CMAKE_CXX_STANDARD 14)

add_executable(SymbolicModelChecking2 main.cpp CTLSolvers/CTLSolver.h FormulaToBDDConverter/FormulaToBDDConverter.cpp FormulaToBDDConverter/FormulaToBDDConverter.h CTLSolvers/SolverFactory.cpp CTLSolvers/SolverFactory.h CTLSolvers/EXSolver.cpp CTLSolvers/EXSolver.h CTLSolvers/AndSolver.cpp CTLSolvers/AndSolver.h CTLSolvers/VarSolvers.cpp CTLSolvers/VarSolvers.h FormulaToBDDConverter/TransitionRelationToBDDConverter.cpp FormulaToBDDConverter/TransitionRelationToBDDConverter.h Globals/GlobalStorage.cpp Globals/GlobalStorage.h CTLSolvers/AXSolver.cpp CTLSolvers/AXSolver.h CTLSolvers/EUSolver.cpp CTLSolvers/EUSolver.h Utils/BDDUtils.cpp Utils/BDDUtils.h FixPoints/leastFixPoint.cpp FixPoints/leastFixPoint.h CTLSolvers/OrSolver.cpp CTLSolvers/OrSolver.h CTLSolvers/NotSolver.cpp CTLSolvers/NotSolver.h BDD_Dumper.cpp BDD_Dumper.h CTLSolvers/AUSolver.cpp CTLSolvers/AUSolver.h CTLSolvers/BooleanSolver.cpp CTLSolvers/BooleanSolver.h CTLSolvers/EFSolver.cpp CTLSolvers/EFSolver.h FixPoints/greatestFixPoint.cpp FixPoints/greatestFixPoint.h CTLSolvers/EGSolver.cpp CTLSolvers/EGSolver.h CTLSolvers/AFSolver.cpp CTLSolvers/AFSolver.h CTLSolvers/AGSolver.cpp CTLSolvers/AGSolver.h CTLSolvers/ERSolver.cpp CTLSolvers/ERSolver.h CTLSolvers/ARSolver.cpp CTLSolvers/ARSolver.h WitnessGenerator/EUWitnessGenerator.cpp WitnessGenerator/EUWitnessGenerator.h)

include_directories(/home/pazhamalai/cudd-3.0.0)
include_directories(/home/pazhamalai/CLionProjects/ModelCheckingInputParser)

find_library(CUDD_LIB libcudd.a /home/pazhamalai/cudd-3.0.0/cudd/.libs)
target_link_libraries(SymbolicModelChecking2 PUBLIC ${CUDD_LIB})

find_library(INPUT_LIB ModelCheckingInputParser /home/pazhamalai/CLionProjects/ModelCheckingInputParser/cmake-build-debug)
target_link_libraries(SymbolicModelChecking2 LINK_PUBLIC ${INPUT_LIB})