CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla
EXEC = testCML

TENSORS = $(wildcard CML/tensors/*.cc)
MODULES = $(wildcard CML/nn/Modules/*.cc)
CONTAINERS = $(wildcard CML/nn/Containers/*.cc)
VARIABLES = $(wildcard CML/nn/Variables/*.cc)
LAYERS = $(wildcard CML/nn/Layers/*.cc)
OPTIMIZER = $(wildcard CML/optim/Optimizers/*.cc)
OBJECTS = $(TENSORS:.cc=.o) $(MODULES:.cc=.o) $(CONTAINERS:.cc=.o) $(VARIABLES:.cc=.o) $(LAYERS:.cc=.o) $(OPTIMIZER:.cc=.o) testCML.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
