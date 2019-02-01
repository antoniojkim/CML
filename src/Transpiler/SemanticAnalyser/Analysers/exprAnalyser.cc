
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_expr_expr16(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr expr16");
    throw "analyse_expr_expr16 not implemented";
}

map<string, AnalysisFunction> analyse_expr_map = {
    {"expr expr16", analyse_expr_expr16}};

AnalysisFunction get_expr_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr_map[nt->getRule()];
}
        