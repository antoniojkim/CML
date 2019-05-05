
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_expr7_expr6(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr7 expr6");
    throw "analyse_expr7_expr6 not implemented";
}
void analyse_expr7_expr7_GT_GT_expr6(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr7 expr7 GT_GT expr6");
    throw "analyse_expr7_expr7_GT_GT_expr6 not implemented";
}
void analyse_expr7_expr7_LT_LT_expr6(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr7 expr7 LT_LT expr6");
    throw "analyse_expr7_expr7_LT_LT_expr6 not implemented";
}

map<string, AnalysisFunction> analyse_expr7_map = {
    {"expr7 expr6", analyse_expr7_expr6},
    {"expr7 expr7 GT_GT expr6", analyse_expr7_expr7_GT_GT_expr6},
    {"expr7 expr7 LT_LT expr6", analyse_expr7_expr7_LT_LT_expr6}};

AnalysisFunction get_expr7_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr7_map[nt->getRule()];
}
        