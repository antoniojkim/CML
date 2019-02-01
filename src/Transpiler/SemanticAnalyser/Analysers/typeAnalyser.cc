
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_type_BOOL(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type BOOL");
    throw "analyse_type_BOOL not implemented";
}
ostream& analyse_type_INT(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type INT");
    throw "analyse_type_INT not implemented";
}
ostream& analyse_type_LONG(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type LONG");
    throw "analyse_type_LONG not implemented";
}
ostream& analyse_type_LONG_LONG(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type LONG LONG");
    throw "analyse_type_LONG_LONG not implemented";
}
ostream& analyse_type_DOUBLE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type DOUBLE");
    throw "analyse_type_DOUBLE not implemented";
}
ostream& analyse_type_FLOAT(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type FLOAT");
    throw "analyse_type_FLOAT not implemented";
}
ostream& analyse_type_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type ID");
    throw "analyse_type_ID not implemented";
}
ostream& analyse_type_VOID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type VOID");
    throw "analyse_type_VOID not implemented";
}

map<string, AnalysisFunction> analyse_type_map = {
    {"type BOOL", analyse_type_BOOL},
    {"type INT", analyse_type_INT},
    {"type LONG", analyse_type_LONG},
    {"type LONG LONG", analyse_type_LONG_LONG},
    {"type DOUBLE", analyse_type_DOUBLE},
    {"type FLOAT", analyse_type_FLOAT},
    {"type ID", analyse_type_ID},
    {"type VOID", analyse_type_VOID}};

AnalysisFunction get_type_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_type_map[nt->getRule()];
}
        