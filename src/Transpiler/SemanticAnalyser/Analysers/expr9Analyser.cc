
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_expr9_expr8(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr9 expr8");
    throw "analyse_expr9_expr8 not implemented";
}
ostream& analyse_expr9_expr9_GT_expr8(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr9 expr9 GT expr8");
    throw "analyse_expr9_expr9_GT_expr8 not implemented";
}
ostream& analyse_expr9_expr9_LT_expr8(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr9 expr9 LT expr8");
    throw "analyse_expr9_expr9_LT_expr8 not implemented";
}
ostream& analyse_expr9_expr9_GE_expr8(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr9 expr9 GE expr8");
    throw "analyse_expr9_expr9_GE_expr8 not implemented";
}
ostream& analyse_expr9_expr9_LE_expr8(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr9 expr9 LE expr8");
    throw "analyse_expr9_expr9_LE_expr8 not implemented";
}

map<string, AnalysisFunction> analyse_expr9_map = {
    {"expr9 expr8", analyse_expr9_expr8},
    {"expr9 expr9 GT expr8", analyse_expr9_expr9_GT_expr8},
    {"expr9 expr9 LT expr8", analyse_expr9_expr9_LT_expr8},
    {"expr9 expr9 GE expr8", analyse_expr9_expr9_GE_expr8},
    {"expr9 expr9 LE expr8", analyse_expr9_expr9_LE_expr8}};

AnalysisFunction get_expr9_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr9_map[nt->getRule()];
}
        