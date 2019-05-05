
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_vtype_signedtype_type(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "vtype signedtype type");
    throw "analyse_vtype_signedtype_type not implemented";
}
void analyse_vtype_signedtype_type_STAR(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "vtype signedtype type STAR");
    throw "analyse_vtype_signedtype_type_STAR not implemented";
}
void analyse_vtype_signedtype_type_AMP(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "vtype signedtype type AMP");
    throw "analyse_vtype_signedtype_type_AMP not implemented";
}

map<string, AnalysisFunction> analyse_vtype_map = {
    {"vtype signedtype type", analyse_vtype_signedtype_type},
    {"vtype signedtype type STAR", analyse_vtype_signedtype_type_STAR},
    {"vtype signedtype type AMP", analyse_vtype_signedtype_type_AMP}};

AnalysisFunction get_vtype_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_vtype_map[nt->getRule()];
}
        