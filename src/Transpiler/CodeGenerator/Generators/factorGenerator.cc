
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_factor_NUM(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor NUM");
    throw "generate_factor_NUM not implemented";
}
ostream& generate_factor_NONE_(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor NONE_");
    throw "generate_factor_NONE_ not implemented";
}
ostream& generate_factor_NULLPTR(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor NULLPTR");
    throw "generate_factor_NULLPTR not implemented";
}
ostream& generate_factor_TRUE_(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor TRUE_");
    throw "generate_factor_TRUE_ not implemented";
}
ostream& generate_factor_FALSE_(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor FALSE_");
    throw "generate_factor_FALSE_ not implemented";
}
ostream& generate_factor_LPAREN_expr_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor LPAREN expr RPAREN");
    throw "generate_factor_LPAREN_expr_RPAREN not implemented";
}
ostream& generate_factor_ID_LSQUARE_expr_RSQUARE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor ID LSQUARE expr RSQUARE");
    throw "generate_factor_ID_LSQUARE_expr_RSQUARE not implemented";
}
ostream& generate_factor_ID_LSQUARE_expr_COLON_expr_RSQUARE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor ID LSQUARE expr COLON expr RSQUARE");
    throw "generate_factor_ID_LSQUARE_expr_COLON_expr_RSQUARE not implemented";
}
ostream& generate_factor_ID_LPAREN_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor ID LPAREN RPAREN");
    throw "generate_factor_ID_LPAREN_RPAREN not implemented";
}
ostream& generate_factor_ID_LPAREN_arglist_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor ID LPAREN arglist RPAREN");
    throw "generate_factor_ID_LPAREN_arglist_RPAREN not implemented";
}
ostream& generate_factor_ID_DOT_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor ID DOT ID");
    throw "generate_factor_ID_DOT_ID not implemented";
}
ostream& generate_factor_ID_DOT_ID_LPAREN_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor ID DOT ID LPAREN RPAREN");
    throw "generate_factor_ID_DOT_ID_LPAREN_RPAREN not implemented";
}
ostream& generate_factor_ID_DOT_ID_LPAREN_arglist_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor ID DOT ID LPAREN arglist RPAREN");
    throw "generate_factor_ID_DOT_ID_LPAREN_arglist_RPAREN not implemented";
}
ostream& generate_factor_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor ID");
    throw "generate_factor_ID not implemented";
}
ostream& generate_factor_AMP_lvalue(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor AMP lvalue");
    throw "generate_factor_AMP_lvalue not implemented";
}
ostream& generate_factor_STAR_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor STAR factor");
    throw "generate_factor_STAR_factor not implemented";
}
ostream& generate_factor_QUOTE_string_QUOTE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor QUOTE string QUOTE");
    throw "generate_factor_QUOTE_string_QUOTE not implemented";
}
ostream& generate_factor_ID_QUOTE_string_QUOTE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "factor ID QUOTE string QUOTE");
    throw "generate_factor_ID_QUOTE_string_QUOTE not implemented";
}

map<string, GenerateFunction> generate_factor_map = {
    {"factor NUM", generate_factor_NUM},
    {"factor NONE_", generate_factor_NONE_},
    {"factor NULLPTR", generate_factor_NULLPTR},
    {"factor TRUE_", generate_factor_TRUE_},
    {"factor FALSE_", generate_factor_FALSE_},
    {"factor LPAREN expr RPAREN", generate_factor_LPAREN_expr_RPAREN},
    {"factor ID LSQUARE expr RSQUARE", generate_factor_ID_LSQUARE_expr_RSQUARE},
    {"factor ID LSQUARE expr COLON expr RSQUARE", generate_factor_ID_LSQUARE_expr_COLON_expr_RSQUARE},
    {"factor ID LPAREN RPAREN", generate_factor_ID_LPAREN_RPAREN},
    {"factor ID LPAREN arglist RPAREN", generate_factor_ID_LPAREN_arglist_RPAREN},
    {"factor ID DOT ID", generate_factor_ID_DOT_ID},
    {"factor ID DOT ID LPAREN RPAREN", generate_factor_ID_DOT_ID_LPAREN_RPAREN},
    {"factor ID DOT ID LPAREN arglist RPAREN", generate_factor_ID_DOT_ID_LPAREN_arglist_RPAREN},
    {"factor ID", generate_factor_ID},
    {"factor AMP lvalue", generate_factor_AMP_lvalue},
    {"factor STAR factor", generate_factor_STAR_factor},
    {"factor QUOTE string QUOTE", generate_factor_QUOTE_string_QUOTE},
    {"factor ID QUOTE string QUOTE", generate_factor_ID_QUOTE_string_QUOTE}};

GenerateFunction get_factor_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_factor_map[nt->getRule()];
}
        