
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_expr6_expr5(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr6 expr5");
    throw "analyse_expr6_expr5 not implemented";
}
ostream& analyse_expr6_expr6_PLUS_expr5(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr6 expr6 PLUS expr5");
    throw "analyse_expr6_expr6_PLUS_expr5 not implemented";
}
ostream& analyse_expr6_expr6_MINUS_expr5(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr6 expr6 MINUS expr5");
    throw "analyse_expr6_expr6_MINUS_expr5 not implemented";
}

map<string, AnalysisFunction> analyse_expr6_map = {
    {"expr6 expr5", analyse_expr6_expr5},
    {"expr6 expr6 PLUS expr5", analyse_expr6_expr6_PLUS_expr5},
    {"expr6 expr6 MINUS expr5", analyse_expr6_expr6_MINUS_expr5}};

AnalysisFunction get_expr6_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr6_map[nt->getRule()];
}
        