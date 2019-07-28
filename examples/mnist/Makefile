CXX = g++
CXXFLAGS = -g -fopenmp -std=c++14 -Wall -MMD -Werror=vla
EXEC = mnist

TENSORS = $(wildcard ../../core/CML/Tensors/*.cc)
MODULES = $(wildcard ../../core/CML/nn/Modules/*.cc)
# OPTIMIZER = $(wildcard CML/optim/Optimizers/*.cc)     $(OPTIMIZER:.cc=.o)
OBJECTS = $(TENSORS:.cc=.o) $(MODULES:.cc=.o) mnist.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
