
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_expr4_expr3(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr4 expr3");
    throw "analyse_expr4_expr3 not implemented";
}
void analyse_expr4_expr4_STAR_STAR_expr3(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr4 expr4 STAR_STAR expr3");
    throw "analyse_expr4_expr4_STAR_STAR_expr3 not implemented";
}

map<string, AnalysisFunction> analyse_expr4_map = {
    {"expr4 expr3", analyse_expr4_expr3},
    {"expr4 expr4 STAR_STAR expr3", analyse_expr4_expr4_STAR_STAR_expr3}};

AnalysisFunction get_expr4_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr4_map[nt->getRule()];
}
        