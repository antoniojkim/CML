
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_expr16_expr15(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr16 expr15");
    throw "analyse_expr16_expr15 not implemented";
}
void analyse_expr16_lvalue_EQUALS_expr15(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr16 lvalue EQUALS expr15");
    throw "analyse_expr16_lvalue_EQUALS_expr15 not implemented";
}
void analyse_expr16_lvalue_PLUS_EQUALS_expr15(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr16 lvalue PLUS_EQUALS expr15");
    throw "analyse_expr16_lvalue_PLUS_EQUALS_expr15 not implemented";
}
void analyse_expr16_lvalue_MINUS_EQUALS_expr15(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr16 lvalue MINUS_EQUALS expr15");
    throw "analyse_expr16_lvalue_MINUS_EQUALS_expr15 not implemented";
}
void analyse_expr16_lvalue_STAR_EQUALS_expr15(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr16 lvalue STAR_EQUALS expr15");
    throw "analyse_expr16_lvalue_STAR_EQUALS_expr15 not implemented";
}
void analyse_expr16_lvalue_SLASH_EQUALS_expr15(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr16 lvalue SLASH_EQUALS expr15");
    throw "analyse_expr16_lvalue_SLASH_EQUALS_expr15 not implemented";
}
void analyse_expr16_lvalue_PCT_EQUALS_expr15(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr16 lvalue PCT_EQUALS expr15");
    throw "analyse_expr16_lvalue_PCT_EQUALS_expr15 not implemented";
}
void analyse_expr16_lvalue_GT_GT_EQUALS_expr15(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr16 lvalue GT_GT_EQUALS expr15");
    throw "analyse_expr16_lvalue_GT_GT_EQUALS_expr15 not implemented";
}
void analyse_expr16_lvalue_LT_LT_EQUALS_expr15(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr16 lvalue LT_LT_EQUALS expr15");
    throw "analyse_expr16_lvalue_LT_LT_EQUALS_expr15 not implemented";
}
void analyse_expr16_lvalue_AMP_EQUALS_expr15(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr16 lvalue AMP_EQUALS expr15");
    throw "analyse_expr16_lvalue_AMP_EQUALS_expr15 not implemented";
}
void analyse_expr16_lvalue_CARET_EQUALS_expr15(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr16 lvalue CARET_EQUALS expr15");
    throw "analyse_expr16_lvalue_CARET_EQUALS_expr15 not implemented";
}
void analyse_expr16_lvalue_PIPE_EQUALS_expr15(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr16 lvalue PIPE_EQUALS expr15");
    throw "analyse_expr16_lvalue_PIPE_EQUALS_expr15 not implemented";
}

map<string, AnalysisFunction> analyse_expr16_map = {
    {"expr16 expr15", analyse_expr16_expr15},
    {"expr16 lvalue EQUALS expr15", analyse_expr16_lvalue_EQUALS_expr15},
    {"expr16 lvalue PLUS_EQUALS expr15", analyse_expr16_lvalue_PLUS_EQUALS_expr15},
    {"expr16 lvalue MINUS_EQUALS expr15", analyse_expr16_lvalue_MINUS_EQUALS_expr15},
    {"expr16 lvalue STAR_EQUALS expr15", analyse_expr16_lvalue_STAR_EQUALS_expr15},
    {"expr16 lvalue SLASH_EQUALS expr15", analyse_expr16_lvalue_SLASH_EQUALS_expr15},
    {"expr16 lvalue PCT_EQUALS expr15", analyse_expr16_lvalue_PCT_EQUALS_expr15},
    {"expr16 lvalue GT_GT_EQUALS expr15", analyse_expr16_lvalue_GT_GT_EQUALS_expr15},
    {"expr16 lvalue LT_LT_EQUALS expr15", analyse_expr16_lvalue_LT_LT_EQUALS_expr15},
    {"expr16 lvalue AMP_EQUALS expr15", analyse_expr16_lvalue_AMP_EQUALS_expr15},
    {"expr16 lvalue CARET_EQUALS expr15", analyse_expr16_lvalue_CARET_EQUALS_expr15},
    {"expr16 lvalue PIPE_EQUALS expr15", analyse_expr16_lvalue_PIPE_EQUALS_expr15}};

AnalysisFunction get_expr16_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr16_map[nt->getRule()];
}
        