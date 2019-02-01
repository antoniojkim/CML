
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr15_expr14(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr15 expr14");
    throw "generate_expr15_expr14 not implemented";
}
ostream& generate_expr15_expr15_PIPE_PIPE_expr14(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr15 expr15 PIPE_PIPE expr14");
    throw "generate_expr15_expr15_PIPE_PIPE_expr14 not implemented";
}

map<string, GenerateFunction> generate_expr15_map = {
    {"expr15 expr14", generate_expr15_expr14},
    {"expr15 expr15 PIPE_PIPE expr14", generate_expr15_expr15_PIPE_PIPE_expr14}};

GenerateFunction get_expr15_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr15_map[nt->getRule()];
}
        