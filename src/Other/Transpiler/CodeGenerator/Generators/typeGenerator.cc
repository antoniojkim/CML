
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_type_BOOL(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type BOOL");
    throw "generate_type_BOOL not implemented";
}
ostream& generate_type_INT(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type INT");
    throw "generate_type_INT not implemented";
}
ostream& generate_type_LONG(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type LONG");
    throw "generate_type_LONG not implemented";
}
ostream& generate_type_LONG_LONG(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type LONG LONG");
    throw "generate_type_LONG_LONG not implemented";
}
ostream& generate_type_DOUBLE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type DOUBLE");
    throw "generate_type_DOUBLE not implemented";
}
ostream& generate_type_FLOAT(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type FLOAT");
    throw "generate_type_FLOAT not implemented";
}
ostream& generate_type_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type ID");
    throw "generate_type_ID not implemented";
}
ostream& generate_type_VOID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type VOID");
    throw "generate_type_VOID not implemented";
}

map<string, GenerateFunction> generate_type_map = {
    {"type BOOL", generate_type_BOOL},
    {"type INT", generate_type_INT},
    {"type LONG", generate_type_LONG},
    {"type LONG LONG", generate_type_LONG_LONG},
    {"type DOUBLE", generate_type_DOUBLE},
    {"type FLOAT", generate_type_FLOAT},
    {"type ID", generate_type_ID},
    {"type VOID", generate_type_VOID}};

GenerateFunction get_type_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_type_map[nt->getRule()];
}
        