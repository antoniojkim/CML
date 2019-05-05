CXX = g++
CXXFLAGS = -g -std=c++14 -DDEBUG -Wall -MMD -Werror=vla
EXEC = main

CODE_GENERATORS = $(wildcard CodeGenerator/Generators/*.cc)
# ContextSensitiveTrees/ContextSensitiveTrees.o ContextSensitiveTrees/GlobalTree.o ContextSensitiveTrees/ProcedureTree.o ContextSensitiveTrees/DclTree.o ContextSensitiveTrees/StatementTree.o ContextSensitiveTrees/ExprTree.o 
OBJECTS = Scanner/scanner.o Parser/parser.o Parser/parsetree.o ContextSensitiveTrees/ContextSensitiveTrees.o CodeGenerator/codeGenerator.o $(CODE_GENERATORS:.cc=.o) utils.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
