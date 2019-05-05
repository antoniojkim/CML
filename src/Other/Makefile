CXX = g++
CXXFLAGS = -Ofast -g -std=c++14 -DDEBUG -Wall -MMD -Werror=vla
EXEC = main

OBJECTS = CML/Functions/roots.o CML/Functions/polynomials.o CML/LinAlg/matrix.o CML/LinAlg/eigen.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
