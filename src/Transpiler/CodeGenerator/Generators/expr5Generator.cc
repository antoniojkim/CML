
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr5_expr4(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr5 expr4");
    throw "generate_expr5_expr4 not implemented";
}
ostream& generate_expr5_expr5_STAR_expr4(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr5 expr5 STAR expr4");
    throw "generate_expr5_expr5_STAR_expr4 not implemented";
}
ostream& generate_expr5_expr5_SLASH_expr4(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr5 expr5 SLASH expr4");
    throw "generate_expr5_expr5_SLASH_expr4 not implemented";
}

map<string, GenerateFunction> generate_expr5_map = {
    {"expr5 expr4", generate_expr5_expr4},
    {"expr5 expr5 STAR expr4", generate_expr5_expr5_STAR_expr4},
    {"expr5 expr5 SLASH expr4", generate_expr5_expr5_SLASH_expr4}};

GenerateFunction get_expr5_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr5_map[nt->getRule()];
}
        