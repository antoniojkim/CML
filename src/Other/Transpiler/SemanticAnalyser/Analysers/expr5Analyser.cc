
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_expr5_expr4(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr5 expr4");
    throw "analyse_expr5_expr4 not implemented";
}
void analyse_expr5_expr5_STAR_expr4(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr5 expr5 STAR expr4");
    throw "analyse_expr5_expr5_STAR_expr4 not implemented";
}
void analyse_expr5_expr5_SLASH_expr4(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr5 expr5 SLASH expr4");
    throw "analyse_expr5_expr5_SLASH_expr4 not implemented";
}

map<string, AnalysisFunction> analyse_expr5_map = {
    {"expr5 expr4", analyse_expr5_expr4},
    {"expr5 expr5 STAR expr4", analyse_expr5_expr5_STAR_expr4},
    {"expr5 expr5 SLASH expr4", analyse_expr5_expr5_SLASH_expr4}};

AnalysisFunction get_expr5_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr5_map[nt->getRule()];
}
        