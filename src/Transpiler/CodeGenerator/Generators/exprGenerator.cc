
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr_term(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr term");
    throw "generate_expr_term not implemented";
}
ostream& generate_expr_expr_PLUS_term(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr expr PLUS term");
    throw "generate_expr_expr_PLUS_term not implemented";
}
ostream& generate_expr_expr_MINUS_term(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr expr MINUS term");
    throw "generate_expr_expr_MINUS_term not implemented";
}

map<string, GenerateFunction> generate_expr_map = {
    {"expr term", generate_expr_term},
    {"expr expr PLUS term", generate_expr_expr_PLUS_term},
    {"expr expr MINUS term", generate_expr_expr_MINUS_term}};

GenerateFunction get_expr_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr_map[nt->getRule()];
}
        