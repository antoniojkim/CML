
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_expr1_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr1 factor");
    throw "analyse_expr1_factor not implemented";
}
ostream& analyse_expr1_lvalue(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr1 lvalue");
    throw "analyse_expr1_lvalue not implemented";
}
ostream& analyse_expr1_ID_COLON_COLON_expr1(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr1 ID COLON_COLON expr1");
    throw "analyse_expr1_ID_COLON_COLON_expr1 not implemented";
}

map<string, AnalysisFunction> analyse_expr1_map = {
    {"expr1 factor", analyse_expr1_factor},
    {"expr1 lvalue", analyse_expr1_lvalue},
    {"expr1 ID COLON_COLON expr1", analyse_expr1_ID_COLON_COLON_expr1}};

AnalysisFunction get_expr1_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr1_map[nt->getRule()];
}
        