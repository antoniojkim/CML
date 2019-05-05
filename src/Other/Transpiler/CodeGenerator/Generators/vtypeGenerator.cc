
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_vtype_signedtype_type(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "vtype signedtype type");
    throw "generate_vtype_signedtype_type not implemented";
}
ostream& generate_vtype_signedtype_type_STAR(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "vtype signedtype type STAR");
    throw "generate_vtype_signedtype_type_STAR not implemented";
}
ostream& generate_vtype_signedtype_type_AMP(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "vtype signedtype type AMP");
    throw "generate_vtype_signedtype_type_AMP not implemented";
}

map<string, GenerateFunction> generate_vtype_map = {
    {"vtype signedtype type", generate_vtype_signedtype_type},
    {"vtype signedtype type STAR", generate_vtype_signedtype_type_STAR},
    {"vtype signedtype type AMP", generate_vtype_signedtype_type_AMP}};

GenerateFunction get_vtype_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_vtype_map[nt->getRule()];
}
        