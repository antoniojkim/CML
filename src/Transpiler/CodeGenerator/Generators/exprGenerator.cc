
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr_expr16(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr expr16");
    throw "generate_expr_expr16 not implemented";
}

map<string, GenerateFunction> generate_expr_map = {
    {"expr expr16", generate_expr_expr16}};

GenerateFunction get_expr_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr_map[nt->getRule()];
}
        