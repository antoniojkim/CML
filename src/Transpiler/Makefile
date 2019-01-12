CXX = g++
CXXFLAGS = -Ofast -g -std=c++14 -DDEBUG -Wall -MMD -Werror=vla
EXEC = main

OBJECTS = Scanner/scanner.o Parser/parser.o Parser/parsetree.o utils.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
