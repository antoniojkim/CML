
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr8_expr7(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr8 expr7");
    throw "generate_expr8_expr7 not implemented";
}

map<string, GenerateFunction> generate_expr8_map = {
    {"expr8 expr7", generate_expr8_expr7}};

GenerateFunction get_expr8_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr8_map[nt->getRule()];
}
        