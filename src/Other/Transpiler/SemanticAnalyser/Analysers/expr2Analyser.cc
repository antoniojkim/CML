
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_expr2_expr1(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr1");
    throw "analyse_expr2_expr1 not implemented";
}
void analyse_expr2_LPAREN_expr_RPAREN(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 LPAREN expr RPAREN");
    throw "analyse_expr2_LPAREN_expr_RPAREN not implemented";
}
void analyse_expr2_expr2_PLUS_PLUS(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 PLUS_PLUS");
    throw "analyse_expr2_expr2_PLUS_PLUS not implemented";
}
void analyse_expr2_expr2_MINUS_MINUS(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 MINUS_MINUS");
    throw "analyse_expr2_expr2_MINUS_MINUS not implemented";
}
void analyse_expr2_ID_LPAREN_RPAREN(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 ID LPAREN RPAREN");
    throw "analyse_expr2_ID_LPAREN_RPAREN not implemented";
}
void analyse_expr2_ID_LPAREN_arglist_RPAREN(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 ID LPAREN arglist RPAREN");
    throw "analyse_expr2_ID_LPAREN_arglist_RPAREN not implemented";
}
void analyse_expr2_ID_LSQUARE_expr_RSQUARE(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 ID LSQUARE expr RSQUARE");
    throw "analyse_expr2_ID_LSQUARE_expr_RSQUARE not implemented";
}
void analyse_expr2_ID_LSQUARE_expr_COLON_expr_RSQUARE(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 ID LSQUARE expr COLON expr RSQUARE");
    throw "analyse_expr2_ID_LSQUARE_expr_COLON_expr_RSQUARE not implemented";
}
void analyse_expr2_QUOTE_string_QUOTE(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 QUOTE string QUOTE");
    throw "analyse_expr2_QUOTE_string_QUOTE not implemented";
}
void analyse_expr2_ID_QUOTE_string_QUOTE(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 ID QUOTE string QUOTE");
    throw "analyse_expr2_ID_QUOTE_string_QUOTE not implemented";
}
void analyse_expr2_expr2_DOT_expr2(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 DOT expr2");
    throw "analyse_expr2_expr2_DOT_expr2 not implemented";
}
void analyse_expr2_expr2_DOT_expr2_LPAREN_RPAREN(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 DOT expr2 LPAREN RPAREN");
    throw "analyse_expr2_expr2_DOT_expr2_LPAREN_RPAREN not implemented";
}
void analyse_expr2_expr2_DOT_expr2_LPAREN_arglist_RPAREN(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 DOT expr2 LPAREN arglist RPAREN");
    throw "analyse_expr2_expr2_DOT_expr2_LPAREN_arglist_RPAREN not implemented";
}
void analyse_expr2_expr2_R_ARROW_expr1(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 R_ARROW expr1");
    throw "analyse_expr2_expr2_R_ARROW_expr1 not implemented";
}
void analyse_expr2_expr2_L_ARROW_expr1(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 L_ARROW expr1");
    throw "analyse_expr2_expr2_L_ARROW_expr1 not implemented";
}

map<string, AnalysisFunction> analyse_expr2_map = {
    {"expr2 expr1", analyse_expr2_expr1},
    {"expr2 LPAREN expr RPAREN", analyse_expr2_LPAREN_expr_RPAREN},
    {"expr2 expr2 PLUS_PLUS", analyse_expr2_expr2_PLUS_PLUS},
    {"expr2 expr2 MINUS_MINUS", analyse_expr2_expr2_MINUS_MINUS},
    {"expr2 ID LPAREN RPAREN", analyse_expr2_ID_LPAREN_RPAREN},
    {"expr2 ID LPAREN arglist RPAREN", analyse_expr2_ID_LPAREN_arglist_RPAREN},
    {"expr2 ID LSQUARE expr RSQUARE", analyse_expr2_ID_LSQUARE_expr_RSQUARE},
    {"expr2 ID LSQUARE expr COLON expr RSQUARE", analyse_expr2_ID_LSQUARE_expr_COLON_expr_RSQUARE},
    {"expr2 QUOTE string QUOTE", analyse_expr2_QUOTE_string_QUOTE},
    {"expr2 ID QUOTE string QUOTE", analyse_expr2_ID_QUOTE_string_QUOTE},
    {"expr2 expr2 DOT expr2", analyse_expr2_expr2_DOT_expr2},
    {"expr2 expr2 DOT expr2 LPAREN RPAREN", analyse_expr2_expr2_DOT_expr2_LPAREN_RPAREN},
    {"expr2 expr2 DOT expr2 LPAREN arglist RPAREN", analyse_expr2_expr2_DOT_expr2_LPAREN_arglist_RPAREN},
    {"expr2 expr2 R_ARROW expr1", analyse_expr2_expr2_R_ARROW_expr1},
    {"expr2 expr2 L_ARROW expr1", analyse_expr2_expr2_L_ARROW_expr1}};

AnalysisFunction get_expr2_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr2_map[nt->getRule()];
}
        