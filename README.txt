1. Features implemented
2. Input file format
3. Where to keep inputs
4. Witness generation
5. Compilation and running
  Dependencies:
    GCC and CMAKE
    CUDD
    ModelCheckingInputParser
    CMakeLists.txt


FEATURES IMPLEMENTED:

    Operations of all CTL operators implemented. In assignment 2 brief, it says that we have to implement all CTL
    operators using their own fixpoints. However, I did fixpoint computation for EX, EG, EU and reused this for all
    other operators

    I implemented fairness for all CTL operators

    I implemented Witness Generation for EU. Since EF is represented as EU, EF also has witness generation. I didn't
    do witness generation for EG. [This witness generation has a bug, which is mentioned at last]



INPUT FILE FORMAT:

    A sample input format is present in location /SymbolicModelChecking2/test/1/data.txt

    I didn't use the MicrowaveOven example. It is present in the directory /SymbolicModelChecking2/test/microwaveOven.
    Because it's transition relation is very huge. Hard to read.

    First line   -> Variable declaration
    Second line  -> Transition relation
    Third line   -> Initial state formula
    Fourth line  -> CTL formula
    Fifth line   -> Fairness constraints

    This program only reads the first five lines. Any lines after those will be ignored. You can use those for comments
    Also empty lines, in any of the first five line means there are no formula specified and it treats as NULL.
    You can have empty line in fairness constraints. All the other parameters should be specified.

    VARIABLE DECLARATION:
            Variables are just space separated names. TRUE, FALSE cannot be used as variables. They are considered as
            boolean constants. In the example data.txt, sweet and candy are variables.

    FORMULA:
            The next 4 lines will be formulas. This is a general info on how to write formulas.
            Example formulas are
            1. (and (sweet) (candy))
            2. (not (candy))
            3. (EX (not (sweet)))
            4. (EU (sweet) (candy))

            I made an assumption that every subformula should be enclosed in brackets. For example, the following
            is valid in SMT-LIB2

            (and sweet candy)

            But this is not valid in my input parser. It demands brackets for every subformulas including variables.
            The correct version is

            (and (sweet) (candy))

            Also EU, ER are typically denoted as E(f1 U f2), E(f1 R f2). But here it should be represented as
            (EU (f1) (f2)), (ER (f1) (f2))

            You can find the supported operator types in enum NodeType. This enum can be found in library
            ModelCheckingInputParser, in file MCIP.h

            https://github.com/pazhamalai/ModelCheckingInputParser


    Transition Relation:
            Transition relation uses both current state and next state variables. To specify a next state variable,
            put a '_' before a normal variable. Note this variable must be declared in the above declaration.
            Example,

            (and (candy) (_sweet))

            The above transition relation means (s.candy ^ s'.sweet).

            The next state variables should only be specified for transition formula.
            If specified for any other formula the input parser will throw error.


    Fairness constraints
            These are just comma separated formulas.


WHERE TO KEEP INPUTS:

    . Create your custom directory inside the directory /SymbolicModelChecking2/test
              [This is a rule i follow to keep inputs organized]
    . Change the variable INPUT_DIRECTORY, in main.cpp to point to this directory.
    . Input should be specified in a file named "data.txt" inside your custom folder.
    . By default, my program will look for data.txt file inside the directory mentioned in INPUT_DIRECTORY variable.

    . After running the program, The BDD for the CTL formula mentioned in input, will automatically be
      stored as a dot file named "graph.dot", inside your custom directory.
    . You can run "dot -Tpng graph.dot -o output.png" to get the image of the BDD. I do this in ubuntu.



WITNESS GENERATION:
     I have done Witness generation only for EU and EF. By default Witness generation is disabled. This is because
     of two reasons

     1. It has a bug. When a EU or EF CTL formula is given, which has no witness, then this witness generation
        crashes. I didn't handle that case. So while testing witness generation make sure you are giving
        a EU / EF formula which has a witness.

     2. For formulas such as (EG (EU (sweet))), this will still generate witness for the inner EU.
        For formulas such as (EU (EU (sweet))), it will generate witness for each EU.

     So witness generation currently works for only one layer CTL formula.
     i.e only the outer formula should be EU/EF.
     Inside them only boolean operators (and, or, not) can be present.

     To enable Witness generation, go to file /SymbolicModelChecking2/CTLSolvers/EUSolver.cpp.
     Change the GENERATE_WITNESS variable to 1.



COMPILATION AND RUNNING:



     A. DEPENDENCIES:

      GCC And CMAKE:

         gcc and cmake should be installed in your system.
         I used "sudo apt install build-essentials" to install these.

         In CMakeLists.txt file which can be found in directory /SymbolicModelChecking2,
         you can see the first line as

         cmake_minimum_required(VERSION 3.19)

         It is automatically generated by my IDE and works in my system, but when tried in Amin's system it throws error.
         In his system cmake version was 3.16.2 i think. So if error is thrown regarding cmake,
         please change this version number as in your system cmake version number. Like the following

         cmake_minimum_required(VERSION 3.16.2)


      CUDD:

         I installed CUDD directly from the source. All three of us, installed directly from the source. The ppa
         doesn't work for us.

         https://davidkebo.com/cudd#cudd2

         In the above link, I downloaded Cudd using option 3 (version 3.0.0). Then i ran "make" command and it
         generated a libCudd.a file.


      ModeCheckingInputParser:

          This is a library i wrote, for reading input file in the input format above mentioned. This can be found
          in the following github link.

          https://github.com/pazhamalai/ModelCheckingInputParser

          After downloading this you have to build this library. For this you can use an IDE such as
          Visual studio code or CLion. In visual studio code, you may need to install cmake plugin.

          Open this project in Visual studio code or CLion. In CLion at the top, a hammer (build) icon will be enabled.
          If you click on that, this project will be built.

          In visual studio code, you can right click the CMakeLists.txt file and click the build option there.

          I don't know how to build a project from terminal.

          After building it this will generate a libModelCheckingInputParser.a file in
          /ModelCheckingInputParser/cmake-build-debug directory.


      CMakeLists.txt

          This file contains the path to libraries CUDD and ModelCheckingInputParser. Change the paths to point
          the libraries in your system.

          In include_library change the path, so that it points to the root directory of the library. It will search
          for header files in this directories.

          In find_library the path will point to the directory which contain the .a file. Example,
          for CUDD, it will have a libCudd.a file inside /cudd-3.0.0/cudd/.libs directory

          for ModelCheckingInputParser, it will have a libModelCheckingInputParser.a file inside
          /ModelCheckingInputParser/cmake-build-debug directory

          After the changes you can run the program. It's easy to run the program from IDE. From terminal, you may
          need to mention some paths i guess.


