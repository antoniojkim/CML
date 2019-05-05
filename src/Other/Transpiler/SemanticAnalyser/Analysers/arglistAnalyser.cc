
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_arglist_expr(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "arglist expr");
    throw "analyse_arglist_expr not implemented";
}
void analyse_arglist_expr_COMMA_arglist(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "arglist expr COMMA arglist");
    throw "analyse_arglist_expr_COMMA_arglist not implemented";
}

map<string, AnalysisFunction> analyse_arglist_map = {
    {"arglist expr", analyse_arglist_expr},
    {"arglist expr COMMA arglist", analyse_arglist_expr_COMMA_arglist}};

AnalysisFunction get_arglist_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_arglist_map[nt->getRule()];
}
        