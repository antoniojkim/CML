CXX = g++
CXXFLAGS = -Ofast -g -std=c++17 -fPIC -Wall -MMD -Werror=vla
TARGET_LIB = libNumeric.a  # target lib

CORE = $(wildcard core/*.cc)

SOURCES = ${CORE}
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${TARGET_LIB}: ${OBJECTS}
	ar rcs ${TARGET_LIB} ${OBJECTS}

# $(SOURCES:.cc=.d):%.d:%.cc
# 	${CXX} ${CXXFLAGS}  -c $< $@

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean