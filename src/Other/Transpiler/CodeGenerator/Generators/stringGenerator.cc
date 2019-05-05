
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_string_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "string ID");
    throw "generate_string_ID not implemented";
}
ostream& generate_string_STR(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "string STR");
    throw "generate_string_STR not implemented";
}

map<string, GenerateFunction> generate_string_map = {
    {"string ID", generate_string_ID},
    {"string STR", generate_string_STR}};

GenerateFunction get_string_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_string_map[nt->getRule()];
}
        