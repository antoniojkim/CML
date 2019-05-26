CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -MMD -Werror=vla
EXEC = testCML

TENSORS = $(wildcard CML/Tensors/*.cc)
PARAMETERS = $(wildcard CML/nn/Parameters/*.cc)
MODULES = $(wildcard CML/nn/Modules/*.cc)
CONTAINERS = $(wildcard CML/nn/Containers/*.cc)
VARIABLES = $(wildcard CML/nn/Variables/*.cc)
LINEAR = $(wildcard CML/nn/Linear/*.cc)
NONLINEAR = $(wildcard CML/nn/Nonlinear/*.cc)
OPTIMIZER = $(wildcard CML/optim/Optimizers/*.cc)
OBJECTS = $(TENSORS:.cc=.o) $(PARAMETERS:.cc=.o) $(MODULES:.cc=.o) $(CONTAINERS:.cc=.o) $(VARIABLES:.cc=.o) $(LINEAR:.cc=.o) $(NONLINEAR:.cc=.o) $(OPTIMIZER:.cc=.o) testCML.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
