
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_factor_NUM(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor NUM");
    throw "generate_factor_NUM not implemented";
}
ostream& generate_factor_NONE_(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor NONE_");
    throw "generate_factor_NONE_ not implemented";
}
ostream& generate_factor_NULLPTR(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor NULLPTR");
    throw "generate_factor_NULLPTR not implemented";
}
ostream& generate_factor_TRUE_(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor TRUE_");
    throw "generate_factor_TRUE_ not implemented";
}
ostream& generate_factor_FALSE_(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor FALSE_");
    throw "generate_factor_FALSE_ not implemented";
}
ostream& generate_factor_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor ID");
    throw "generate_factor_ID not implemented";
}

map<string, GenerateFunction> generate_factor_map = {
    {"factor NUM", generate_factor_NUM},
    {"factor NONE_", generate_factor_NONE_},
    {"factor NULLPTR", generate_factor_NULLPTR},
    {"factor TRUE_", generate_factor_TRUE_},
    {"factor FALSE_", generate_factor_FALSE_},
    {"factor ID", generate_factor_ID}};

GenerateFunction get_factor_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_factor_map[nt->getRule()];
}
        