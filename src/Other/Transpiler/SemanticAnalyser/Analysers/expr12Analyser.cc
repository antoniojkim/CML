
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_expr12_expr11(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr12 expr11");
    throw "analyse_expr12_expr11 not implemented";
}
void analyse_expr12_expr12_CARET_expr11(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr12 expr12 CARET expr11");
    throw "analyse_expr12_expr12_CARET_expr11 not implemented";
}

map<string, AnalysisFunction> analyse_expr12_map = {
    {"expr12 expr11", analyse_expr12_expr11},
    {"expr12 expr12 CARET expr11", analyse_expr12_expr12_CARET_expr11}};

AnalysisFunction get_expr12_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr12_map[nt->getRule()];
}
        