
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_expr14_expr13(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr14 expr13");
    throw "analyse_expr14_expr13 not implemented";
}
ostream& analyse_expr14_expr14_AMP_AMP_expr13(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr14 expr14 AMP_AMP expr13");
    throw "analyse_expr14_expr14_AMP_AMP_expr13 not implemented";
}

map<string, AnalysisFunction> analyse_expr14_map = {
    {"expr14 expr13", analyse_expr14_expr13},
    {"expr14 expr14 AMP_AMP expr13", analyse_expr14_expr14_AMP_AMP_expr13}};

AnalysisFunction get_expr14_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr14_map[nt->getRule()];
}
        