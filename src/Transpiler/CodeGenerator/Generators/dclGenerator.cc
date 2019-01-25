
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_dcl_vtype_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "dcl vtype ID");
    throw "generate_dcl_vtype_ID not implemented";
}
ostream& generate_dcl_vtype_ID_EQUALS_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "dcl vtype ID EQUALS expr");
    throw "generate_dcl_vtype_ID_EQUALS_expr not implemented";
}

map<string, GenerateFunction> generate_dcl_map = {
    {"dcl vtype ID", generate_dcl_vtype_ID},
    {"dcl vtype ID EQUALS expr", generate_dcl_vtype_ID_EQUALS_expr}};

GenerateFunction get_dcl_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_dcl_map[nt->getRule()];
}
        