CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -MMD -Werror=vla -DDEBUG -I $${HOME} -I ../core/
EXEC = test

NUMERIC_TESTS = $(wildcard numeric/*.cc)

SOURCES = ${NUMERIC_TESTS} test.cc 
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L../core/Numeric/ -lNumeric 

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
