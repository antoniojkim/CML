
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_expr11_expr10(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr11 expr10");
    throw "analyse_expr11_expr10 not implemented";
}
void analyse_expr11_expr11_AMP_expr10(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr11 expr11 AMP expr10");
    throw "analyse_expr11_expr11_AMP_expr10 not implemented";
}

map<string, AnalysisFunction> analyse_expr11_map = {
    {"expr11 expr10", analyse_expr11_expr10},
    {"expr11 expr11 AMP expr10", analyse_expr11_expr11_AMP_expr10}};

AnalysisFunction get_expr11_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr11_map[nt->getRule()];
}
        