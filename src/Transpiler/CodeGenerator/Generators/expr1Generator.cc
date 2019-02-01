
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr1_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr1 factor");
    throw "generate_expr1_factor not implemented";
}
ostream& generate_expr1_lvalue(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr1 lvalue");
    throw "generate_expr1_lvalue not implemented";
}
ostream& generate_expr1_ID_COLON_COLON_expr1(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr1 ID COLON_COLON expr1");
    throw "generate_expr1_ID_COLON_COLON_expr1 not implemented";
}

map<string, GenerateFunction> generate_expr1_map = {
    {"expr1 factor", generate_expr1_factor},
    {"expr1 lvalue", generate_expr1_lvalue},
    {"expr1 ID COLON_COLON expr1", generate_expr1_ID_COLON_COLON_expr1}};

GenerateFunction get_expr1_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr1_map[nt->getRule()];
}
        