
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr6_expr5(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr6 expr5");
    throw "generate_expr6_expr5 not implemented";
}
ostream& generate_expr6_expr6_PLUS_expr5(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr6 expr6 PLUS expr5");
    throw "generate_expr6_expr6_PLUS_expr5 not implemented";
}
ostream& generate_expr6_expr6_MINUS_expr5(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr6 expr6 MINUS expr5");
    throw "generate_expr6_expr6_MINUS_expr5 not implemented";
}

map<string, GenerateFunction> generate_expr6_map = {
    {"expr6 expr5", generate_expr6_expr5},
    {"expr6 expr6 PLUS expr5", generate_expr6_expr6_PLUS_expr5},
    {"expr6 expr6 MINUS expr5", generate_expr6_expr6_MINUS_expr5}};

GenerateFunction get_expr6_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr6_map[nt->getRule()];
}
        