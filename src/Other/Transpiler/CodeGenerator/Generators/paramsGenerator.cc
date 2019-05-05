
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_params_dcl_params(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "params dcl params");
    throw "generate_params_dcl_params not implemented";
}

map<string, GenerateFunction> generate_params_map = {
    {"params dcl params", generate_params_dcl_params}};

GenerateFunction get_params_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_params_map[nt->getRule()];
}
        