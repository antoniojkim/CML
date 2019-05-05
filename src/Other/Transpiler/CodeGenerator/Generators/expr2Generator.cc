
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_expr2_expr1(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr1");
    throw "generate_expr2_expr1 not implemented";
}
ostream& generate_expr2_LPAREN_expr_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 LPAREN expr RPAREN");
    throw "generate_expr2_LPAREN_expr_RPAREN not implemented";
}
ostream& generate_expr2_expr2_PLUS_PLUS(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 PLUS_PLUS");
    throw "generate_expr2_expr2_PLUS_PLUS not implemented";
}
ostream& generate_expr2_expr2_MINUS_MINUS(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 MINUS_MINUS");
    throw "generate_expr2_expr2_MINUS_MINUS not implemented";
}
ostream& generate_expr2_ID_LPAREN_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 ID LPAREN RPAREN");
    throw "generate_expr2_ID_LPAREN_RPAREN not implemented";
}
ostream& generate_expr2_ID_LPAREN_arglist_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 ID LPAREN arglist RPAREN");
    throw "generate_expr2_ID_LPAREN_arglist_RPAREN not implemented";
}
ostream& generate_expr2_ID_LSQUARE_expr_RSQUARE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 ID LSQUARE expr RSQUARE");
    throw "generate_expr2_ID_LSQUARE_expr_RSQUARE not implemented";
}
ostream& generate_expr2_ID_LSQUARE_expr_COLON_expr_RSQUARE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 ID LSQUARE expr COLON expr RSQUARE");
    throw "generate_expr2_ID_LSQUARE_expr_COLON_expr_RSQUARE not implemented";
}
ostream& generate_expr2_QUOTE_string_QUOTE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 QUOTE string QUOTE");
    throw "generate_expr2_QUOTE_string_QUOTE not implemented";
}
ostream& generate_expr2_ID_QUOTE_string_QUOTE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 ID QUOTE string QUOTE");
    throw "generate_expr2_ID_QUOTE_string_QUOTE not implemented";
}
ostream& generate_expr2_expr2_DOT_expr2(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 DOT expr2");
    throw "generate_expr2_expr2_DOT_expr2 not implemented";
}
ostream& generate_expr2_expr2_DOT_expr2_LPAREN_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 DOT expr2 LPAREN RPAREN");
    throw "generate_expr2_expr2_DOT_expr2_LPAREN_RPAREN not implemented";
}
ostream& generate_expr2_expr2_DOT_expr2_LPAREN_arglist_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 DOT expr2 LPAREN arglist RPAREN");
    throw "generate_expr2_expr2_DOT_expr2_LPAREN_arglist_RPAREN not implemented";
}
ostream& generate_expr2_expr2_R_ARROW_expr1(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 R_ARROW expr1");
    throw "generate_expr2_expr2_R_ARROW_expr1 not implemented";
}
ostream& generate_expr2_expr2_L_ARROW_expr1(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr2 expr2 L_ARROW expr1");
    throw "generate_expr2_expr2_L_ARROW_expr1 not implemented";
}

map<string, GenerateFunction> generate_expr2_map = {
    {"expr2 expr1", generate_expr2_expr1},
    {"expr2 LPAREN expr RPAREN", generate_expr2_LPAREN_expr_RPAREN},
    {"expr2 expr2 PLUS_PLUS", generate_expr2_expr2_PLUS_PLUS},
    {"expr2 expr2 MINUS_MINUS", generate_expr2_expr2_MINUS_MINUS},
    {"expr2 ID LPAREN RPAREN", generate_expr2_ID_LPAREN_RPAREN},
    {"expr2 ID LPAREN arglist RPAREN", generate_expr2_ID_LPAREN_arglist_RPAREN},
    {"expr2 ID LSQUARE expr RSQUARE", generate_expr2_ID_LSQUARE_expr_RSQUARE},
    {"expr2 ID LSQUARE expr COLON expr RSQUARE", generate_expr2_ID_LSQUARE_expr_COLON_expr_RSQUARE},
    {"expr2 QUOTE string QUOTE", generate_expr2_QUOTE_string_QUOTE},
    {"expr2 ID QUOTE string QUOTE", generate_expr2_ID_QUOTE_string_QUOTE},
    {"expr2 expr2 DOT expr2", generate_expr2_expr2_DOT_expr2},
    {"expr2 expr2 DOT expr2 LPAREN RPAREN", generate_expr2_expr2_DOT_expr2_LPAREN_RPAREN},
    {"expr2 expr2 DOT expr2 LPAREN arglist RPAREN", generate_expr2_expr2_DOT_expr2_LPAREN_arglist_RPAREN},
    {"expr2 expr2 R_ARROW expr1", generate_expr2_expr2_R_ARROW_expr1},
    {"expr2 expr2 L_ARROW expr1", generate_expr2_expr2_L_ARROW_expr1}};

GenerateFunction get_expr2_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_expr2_map[nt->getRule()];
}
        