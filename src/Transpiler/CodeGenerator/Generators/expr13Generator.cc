
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr13_expr12(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr13 expr12");
    throw "generate_expr13_expr12 not implemented";
}
ostream& generate_expr13_expr13_PIPE_expr12(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr13 expr13 PIPE expr12");
    throw "generate_expr13_expr13_PIPE_expr12 not implemented";
}

map<string, GenerateFunction> generate_expr13_map = {
    {"expr13 expr12", generate_expr13_expr12},
    {"expr13 expr13 PIPE expr12", generate_expr13_expr13_PIPE_expr12}};

GenerateFunction get_expr13_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr13_map[nt->getRule()];
}
        