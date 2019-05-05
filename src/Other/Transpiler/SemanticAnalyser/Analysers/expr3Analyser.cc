
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_expr3_expr2(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr3 expr2");
    throw "analyse_expr3_expr2 not implemented";
}
void analyse_expr3_PLUS_PLUS_expr2(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr3 PLUS_PLUS expr2");
    throw "analyse_expr3_PLUS_PLUS_expr2 not implemented";
}
void analyse_expr3_MINUS_MINUS_expr2(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr3 MINUS_MINUS expr2");
    throw "analyse_expr3_MINUS_MINUS_expr2 not implemented";
}
void analyse_expr3_PLUS_expr2(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr3 PLUS expr2");
    throw "analyse_expr3_PLUS_expr2 not implemented";
}
void analyse_expr3_MINUS_expr2(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr3 MINUS expr2");
    throw "analyse_expr3_MINUS_expr2 not implemented";
}
void analyse_expr3_EXCL_expr2(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr3 EXCL expr2");
    throw "analyse_expr3_EXCL_expr2 not implemented";
}
void analyse_expr3_TILDE_expr2(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr3 TILDE expr2");
    throw "analyse_expr3_TILDE_expr2 not implemented";
}
void analyse_expr3_STAR_expr2(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr3 STAR expr2");
    throw "analyse_expr3_STAR_expr2 not implemented";
}
void analyse_expr3_AMP_expr2(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr3 AMP expr2");
    throw "analyse_expr3_AMP_expr2 not implemented";
}

map<string, AnalysisFunction> analyse_expr3_map = {
    {"expr3 expr2", analyse_expr3_expr2},
    {"expr3 PLUS_PLUS expr2", analyse_expr3_PLUS_PLUS_expr2},
    {"expr3 MINUS_MINUS expr2", analyse_expr3_MINUS_MINUS_expr2},
    {"expr3 PLUS expr2", analyse_expr3_PLUS_expr2},
    {"expr3 MINUS expr2", analyse_expr3_MINUS_expr2},
    {"expr3 EXCL expr2", analyse_expr3_EXCL_expr2},
    {"expr3 TILDE expr2", analyse_expr3_TILDE_expr2},
    {"expr3 STAR expr2", analyse_expr3_STAR_expr2},
    {"expr3 AMP expr2", analyse_expr3_AMP_expr2}};

AnalysisFunction get_expr3_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr3_map[nt->getRule()];
}
        