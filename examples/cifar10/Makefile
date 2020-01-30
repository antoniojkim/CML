CXX = g++
CXXFLAGS = -g -std=c++17 -I../../ -Wall -MMD -Werror=vla # -DTEST # -DDEBUG
EXEC = cifar10

OBJECTS = cifar10.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
