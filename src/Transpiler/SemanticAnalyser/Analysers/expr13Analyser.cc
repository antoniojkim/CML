
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_expr13_expr12(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr13 expr12");
    throw "analyse_expr13_expr12 not implemented";
}
ostream& analyse_expr13_expr13_PIPE_expr12(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr13 expr13 PIPE expr12");
    throw "analyse_expr13_expr13_PIPE_expr12 not implemented";
}

map<string, AnalysisFunction> analyse_expr13_map = {
    {"expr13 expr12", analyse_expr13_expr12},
    {"expr13 expr13 PIPE expr12", analyse_expr13_expr13_PIPE_expr12}};

AnalysisFunction get_expr13_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr13_map[nt->getRule()];
}
        