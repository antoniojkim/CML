
#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <iostream>
#include <map>
#include <string>
#include "../ContextSensitiveTrees/ContextSensitiveTrees.h"
#include "../Parser/parsetree.h"

typedef std::ostream& (*GenerateFunction)(ContextSensitiveTree* tree, std::ostream& out, const std::string& indent);

GenerateFunction getCodeGenerationFunction(ParseTree* tree);

#endif // CODE_GENERATOR_H
    
