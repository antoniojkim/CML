
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr10_expr9(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr10 expr9");
    throw "generate_expr10_expr9 not implemented";
}
ostream& generate_expr10_expr10_EQUALS_EQUALS_expr9(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr10 expr10 EQUALS_EQUALS expr9");
    throw "generate_expr10_expr10_EQUALS_EQUALS_expr9 not implemented";
}
ostream& generate_expr10_expr10_NE_expr9(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr10 expr10 NE expr9");
    throw "generate_expr10_expr10_NE_expr9 not implemented";
}
ostream& generate_expr10_expr10_QE_expr9(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr10 expr10 QE expr9");
    throw "generate_expr10_expr10_QE_expr9 not implemented";
}

map<string, GenerateFunction> generate_expr10_map = {
    {"expr10 expr9", generate_expr10_expr9},
    {"expr10 expr10 EQUALS_EQUALS expr9", generate_expr10_expr10_EQUALS_EQUALS_expr9},
    {"expr10 expr10 NE expr9", generate_expr10_expr10_NE_expr9},
    {"expr10 expr10 QE expr9", generate_expr10_expr10_QE_expr9}};

GenerateFunction get_expr10_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr10_map[nt->getRule()];
}
        