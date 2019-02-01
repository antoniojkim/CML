
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr4_expr3(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr4 expr3");
    throw "generate_expr4_expr3 not implemented";
}
ostream& generate_expr4_expr4_STAR_STAR_expr3(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr4 expr4 STAR_STAR expr3");
    throw "generate_expr4_expr4_STAR_STAR_expr3 not implemented";
}

map<string, GenerateFunction> generate_expr4_map = {
    {"expr4 expr3", generate_expr4_expr3},
    {"expr4 expr4 STAR_STAR expr3", generate_expr4_expr4_STAR_STAR_expr3}};

GenerateFunction get_expr4_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr4_map[nt->getRule()];
}
        