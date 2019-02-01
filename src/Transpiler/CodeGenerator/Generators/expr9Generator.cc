
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr9_expr8(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr9 expr8");
    throw "generate_expr9_expr8 not implemented";
}
ostream& generate_expr9_expr9_GT_expr8(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr9 expr9 GT expr8");
    throw "generate_expr9_expr9_GT_expr8 not implemented";
}
ostream& generate_expr9_expr9_LT_expr8(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr9 expr9 LT expr8");
    throw "generate_expr9_expr9_LT_expr8 not implemented";
}
ostream& generate_expr9_expr9_GE_expr8(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr9 expr9 GE expr8");
    throw "generate_expr9_expr9_GE_expr8 not implemented";
}
ostream& generate_expr9_expr9_LE_expr8(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr9 expr9 LE expr8");
    throw "generate_expr9_expr9_LE_expr8 not implemented";
}

map<string, GenerateFunction> generate_expr9_map = {
    {"expr9 expr8", generate_expr9_expr8},
    {"expr9 expr9 GT expr8", generate_expr9_expr9_GT_expr8},
    {"expr9 expr9 LT expr8", generate_expr9_expr9_LT_expr8},
    {"expr9 expr9 GE expr8", generate_expr9_expr9_GE_expr8},
    {"expr9 expr9 LE expr8", generate_expr9_expr9_LE_expr8}};

GenerateFunction get_expr9_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr9_map[nt->getRule()];
}
        