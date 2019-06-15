CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla
EXEC = testCML

TENSORS = $(wildcard CML/Tensors/*.cc)
# PARAMETERS = $(wildcard CML/nn/Parameters/*.cc)   $(PARAMETERS:.cc=.o)
MODULES = $(wildcard CML/nn/Modules/*.cc)
CONTAINERS = $(wildcard CML/nn/Containers/*.cc)
VARIABLES = $(wildcard CML/nn/Variables/*.cc)
LINEAR = $(wildcard CML/nn/Linear/*.cc)
NONLINEAR = $(wildcard CML/nn/Nonlinear/*.cc)
LOSS = $(wildcard CML/nn/Loss/*.cc)
# OPTIMIZER = $(wildcard CML/optim/Optimizers/*.cc)     $(OPTIMIZER:.cc=.o)
OBJECTS = $(TENSORS:.cc=.o) $(F_LINEAR:.cc=.o) $(F_NONLINEAR:.cc=.o) $(MODULES:.cc=.o) $(CONTAINERS:.cc=.o) $(LINEAR:.cc=.o) $(NONLINEAR:.cc=.o) $(LOSS:.cc=.o) testCML.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
