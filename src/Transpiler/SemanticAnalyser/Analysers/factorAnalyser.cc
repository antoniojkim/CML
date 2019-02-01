
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_factor_NUM(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor NUM");
    throw "analyse_factor_NUM not implemented";
}
ostream& analyse_factor_NONE_(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor NONE_");
    throw "analyse_factor_NONE_ not implemented";
}
ostream& analyse_factor_NULLPTR(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor NULLPTR");
    throw "analyse_factor_NULLPTR not implemented";
}
ostream& analyse_factor_TRUE_(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor TRUE_");
    throw "analyse_factor_TRUE_ not implemented";
}
ostream& analyse_factor_FALSE_(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor FALSE_");
    throw "analyse_factor_FALSE_ not implemented";
}
ostream& analyse_factor_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor ID");
    throw "analyse_factor_ID not implemented";
}

map<string, AnalysisFunction> analyse_factor_map = {
    {"factor NUM", analyse_factor_NUM},
    {"factor NONE_", analyse_factor_NONE_},
    {"factor NULLPTR", analyse_factor_NULLPTR},
    {"factor TRUE_", analyse_factor_TRUE_},
    {"factor FALSE_", analyse_factor_FALSE_},
    {"factor ID", analyse_factor_ID}};

AnalysisFunction get_factor_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_factor_map[nt->getRule()];
}
        