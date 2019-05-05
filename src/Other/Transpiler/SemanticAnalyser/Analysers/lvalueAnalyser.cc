
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_lvalue_ID(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "lvalue ID");
    throw "analyse_lvalue_ID not implemented";
}
void analyse_lvalue_STAR_expr2(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "lvalue STAR expr2");
    throw "analyse_lvalue_STAR_expr2 not implemented";
}
void analyse_lvalue_LPAREN_lvalue_RPAREN(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "lvalue LPAREN lvalue RPAREN");
    throw "analyse_lvalue_LPAREN_lvalue_RPAREN not implemented";
}

map<string, AnalysisFunction> analyse_lvalue_map = {
    {"lvalue ID", analyse_lvalue_ID},
    {"lvalue STAR expr2", analyse_lvalue_STAR_expr2},
    {"lvalue LPAREN lvalue RPAREN", analyse_lvalue_LPAREN_lvalue_RPAREN}};

AnalysisFunction get_lvalue_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_lvalue_map[nt->getRule()];
}
        