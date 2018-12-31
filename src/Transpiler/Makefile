CXX = g++
CXXFLAGS = -Ofast -std=c++14 -DDEBUG -Wall -MMD -Werror=vla
EXEC = main

OBJECTS = Scanner/scanner.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
