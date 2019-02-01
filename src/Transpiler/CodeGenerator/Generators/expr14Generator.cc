
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr14_expr13(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr14 expr13");
    throw "generate_expr14_expr13 not implemented";
}
ostream& generate_expr14_expr14_AMP_AMP_expr13(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr14 expr14 AMP_AMP expr13");
    throw "generate_expr14_expr14_AMP_AMP_expr13 not implemented";
}

map<string, GenerateFunction> generate_expr14_map = {
    {"expr14 expr13", generate_expr14_expr13},
    {"expr14 expr14 AMP_AMP expr13", generate_expr14_expr14_AMP_AMP_expr13}};

GenerateFunction get_expr14_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr14_map[nt->getRule()];
}
        