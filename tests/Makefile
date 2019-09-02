CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla -DDEBUG
EXEC = testCML

# TENSORS = $(wildcard ../core/CML/Tensors/*.cc)        $(TENSORS:.cc=.o)
# MODULES = $(wildcard ../core/CML/nn/Modules/*.cc)     $(MODULES:.cc=.o)
# OPTIMIZER = $(wildcard CML/optim/Optimizers/*.cc)     $(OPTIMIZER:.cc=.o)
OBJECTS =  testCML.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
