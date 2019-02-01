
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr7_expr6(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr7 expr6");
    throw "generate_expr7_expr6 not implemented";
}
ostream& generate_expr7_expr7_GT_GT_expr6(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr7 expr7 GT_GT expr6");
    throw "generate_expr7_expr7_GT_GT_expr6 not implemented";
}
ostream& generate_expr7_expr7_LT_LT_expr6(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr7 expr7 LT_LT expr6");
    throw "generate_expr7_expr7_LT_LT_expr6 not implemented";
}

map<string, GenerateFunction> generate_expr7_map = {
    {"expr7 expr6", generate_expr7_expr6},
    {"expr7 expr7 GT_GT expr6", generate_expr7_expr7_GT_GT_expr6},
    {"expr7 expr7 LT_LT expr6", generate_expr7_expr7_LT_LT_expr6}};

GenerateFunction get_expr7_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr7_map[nt->getRule()];
}
        