
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr11_expr10(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr11 expr10");
    throw "generate_expr11_expr10 not implemented";
}
ostream& generate_expr11_expr11_AMP_expr10(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr11 expr11 AMP expr10");
    throw "generate_expr11_expr11_AMP_expr10 not implemented";
}

map<string, GenerateFunction> generate_expr11_map = {
    {"expr11 expr10", generate_expr11_expr10},
    {"expr11 expr11 AMP expr10", generate_expr11_expr11_AMP_expr10}};

GenerateFunction get_expr11_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr11_map[nt->getRule()];
}
        