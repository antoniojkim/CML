
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_include_POUND_INCLUDE_LT_ID_GT(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "include POUND INCLUDE LT ID GT");
    throw "generate_include_POUND_INCLUDE_LT_ID_GT not implemented";
}
ostream& generate_include_POUND_INCLUDE_QUOTE_ID_QUOTE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "include POUND INCLUDE QUOTE ID QUOTE");
    throw "generate_include_POUND_INCLUDE_QUOTE_ID_QUOTE not implemented";
}

map<string, GenerateFunction> generate_include_map = {
    {"include POUND INCLUDE LT ID GT", generate_include_POUND_INCLUDE_LT_ID_GT},
    {"include POUND INCLUDE QUOTE ID QUOTE", generate_include_POUND_INCLUDE_QUOTE_ID_QUOTE}};

GenerateFunction get_include_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_include_map[nt->getRule()];
}
        