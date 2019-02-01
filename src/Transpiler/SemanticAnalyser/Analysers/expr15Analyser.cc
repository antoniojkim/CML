
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_expr15_expr14(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr15 expr14");
    throw "analyse_expr15_expr14 not implemented";
}
ostream& analyse_expr15_expr15_PIPE_PIPE_expr14(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr15 expr15 PIPE_PIPE expr14");
    throw "analyse_expr15_expr15_PIPE_PIPE_expr14 not implemented";
}

map<string, AnalysisFunction> analyse_expr15_map = {
    {"expr15 expr14", analyse_expr15_expr14},
    {"expr15 expr15 PIPE_PIPE expr14", analyse_expr15_expr15_PIPE_PIPE_expr14}};

AnalysisFunction get_expr15_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr15_map[nt->getRule()];
}
        