
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_expr10_expr9(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr10 expr9");
    throw "analyse_expr10_expr9 not implemented";
}
void analyse_expr10_expr10_EQUALS_EQUALS_expr9(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr10 expr10 EQUALS_EQUALS expr9");
    throw "analyse_expr10_expr10_EQUALS_EQUALS_expr9 not implemented";
}
void analyse_expr10_expr10_NE_expr9(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr10 expr10 NE expr9");
    throw "analyse_expr10_expr10_NE_expr9 not implemented";
}
void analyse_expr10_expr10_QE_expr9(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr10 expr10 QE expr9");
    throw "analyse_expr10_expr10_QE_expr9 not implemented";
}

map<string, AnalysisFunction> analyse_expr10_map = {
    {"expr10 expr9", analyse_expr10_expr9},
    {"expr10 expr10 EQUALS_EQUALS expr9", analyse_expr10_expr10_EQUALS_EQUALS_expr9},
    {"expr10 expr10 NE expr9", analyse_expr10_expr10_NE_expr9},
    {"expr10 expr10 QE expr9", analyse_expr10_expr10_QE_expr9}};

AnalysisFunction get_expr10_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr10_map[nt->getRule()];
}
        