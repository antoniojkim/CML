
#include "./codeGenerator.h"
#include <cassert>

using namespace std;
    
// globals
ostream& generate_globals_include_globals(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "globals include globals");
    throw "generate_globals_include_globals not implemented";
}
ostream& generate_globals_procedure_globals(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "globals procedure globals");
    throw "generate_globals_procedure_globals not implemented";
}

// include
ostream& generate_include_POUND_INCLUDE_LT_ID_GT(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "include POUND INCLUDE LT ID GT");
    throw "generate_include_POUND_INCLUDE_LT_ID_GT not implemented";
}
ostream& generate_include_POUND_INCLUDE_QUOTE_ID_QUOTE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "include POUND INCLUDE QUOTE ID QUOTE");
    throw "generate_include_POUND_INCLUDE_QUOTE_ID_QUOTE not implemented";
}

// procedure
ostream& generate_procedure_vtype_ID_LPAREN_params_RPAREN_LBRACE_statements_RBRACE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "procedure vtype ID LPAREN params RPAREN LBRACE statements RBRACE");
    throw "generate_procedure_vtype_ID_LPAREN_params_RPAREN_LBRACE_statements_RBRACE not implemented";
}

// params
ostream& generate_params_dcl_params(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "params dcl params");
    throw "generate_params_dcl_params not implemented";
}

// dcl
ostream& generate_dcl_vtype_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "dcl vtype ID");
    throw "generate_dcl_vtype_ID not implemented";
}
ostream& generate_dcl_vtype_ID_EQUALS_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "dcl vtype ID EQUALS expr");
    throw "generate_dcl_vtype_ID_EQUALS_expr not implemented";
}

// vtype
ostream& generate_vtype_signedtype_type(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "vtype signedtype type");
    throw "generate_vtype_signedtype_type not implemented";
}
ostream& generate_vtype_signedtype_type_STAR(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "vtype signedtype type STAR");
    throw "generate_vtype_signedtype_type_STAR not implemented";
}
ostream& generate_vtype_signedtype_type_AMP(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "vtype signedtype type AMP");
    throw "generate_vtype_signedtype_type_AMP not implemented";
}

// signedtype
ostream& generate_signedtype_UNSIGNED(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "signedtype UNSIGNED");
    throw "generate_signedtype_UNSIGNED not implemented";
}

// type
ostream& generate_type_BOOL(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type BOOL");
    throw "generate_type_BOOL not implemented";
}
ostream& generate_type_INT(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type INT");
    throw "generate_type_INT not implemented";
}
ostream& generate_type_LONG(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type LONG");
    throw "generate_type_LONG not implemented";
}
ostream& generate_type_LONG_LONG(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type LONG LONG");
    throw "generate_type_LONG_LONG not implemented";
}
ostream& generate_type_DOUBLE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type DOUBLE");
    throw "generate_type_DOUBLE not implemented";
}
ostream& generate_type_FLOAT(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type FLOAT");
    throw "generate_type_FLOAT not implemented";
}
ostream& generate_type_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type ID");
    throw "generate_type_ID not implemented";
}
ostream& generate_type_VOID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "type VOID");
    throw "generate_type_VOID not implemented";
}

// statements
ostream& generate_statements_statements_statement(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "statements statements statement");
    throw "generate_statements_statements_statement not implemented";
}

// statement
ostream& generate_statement_dcl_SEMICOLON(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "statement dcl SEMICOLON");
    throw "generate_statement_dcl_SEMICOLON not implemented";
}
ostream& generate_statement_IF_LPAREN_boolean_RPAREN_LBRACE_statements_RBRACE_elseifstatement_elsestatement(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule ==
           "statement IF LPAREN boolean RPAREN LBRACE statements RBRACE elseifstatement elsestatement");
    throw "generate_statement_IF_LPAREN_boolean_RPAREN_LBRACE_statements_RBRACE_elseifstatement_elsestatement not implemented";
}
ostream& generate_statement_RETURN_expr_SEMICOLON(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "statement RETURN expr SEMICOLON");
    throw "generate_statement_RETURN_expr_SEMICOLON not implemented";
}

// elseifstatement
ostream& generate_elseifstatement_ELSE_IF_LPAREN_boolean_RPAREN_LBRACE_statements_RBRACE_elseifstatement(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule ==
           "elseifstatement ELSE IF LPAREN boolean RPAREN LBRACE statements RBRACE elseifstatement");
    throw "generate_elseifstatement_ELSE_IF_LPAREN_boolean_RPAREN_LBRACE_statements_RBRACE_elseifstatement not implemented";
}

// elsestatement
ostream& generate_elsestatement_ELSE_LBRACE_statements_RBRACE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "elsestatement ELSE LBRACE statements RBRACE");
    throw "generate_elsestatement_ELSE_LBRACE_statements_RBRACE not implemented";
}

// boolean
ostream& generate_boolean_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr");
    throw "generate_boolean_expr not implemented";
}
ostream& generate_boolean_NOT_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean NOT expr");
    throw "generate_boolean_NOT_expr not implemented";
}
ostream& generate_boolean_expr_GT_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr GT expr");
    throw "generate_boolean_expr_GT_expr not implemented";
}
ostream& generate_boolean_expr_GE_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr GE expr");
    throw "generate_boolean_expr_GE_expr not implemented";
}
ostream& generate_boolean_expr_LT_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr LT expr");
    throw "generate_boolean_expr_LT_expr not implemented";
}
ostream& generate_boolean_expr_LE_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr LE expr");
    throw "generate_boolean_expr_LE_expr not implemented";
}
ostream& generate_boolean_expr_NE_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr NE expr");
    throw "generate_boolean_expr_NE_expr not implemented";
}
ostream& generate_boolean_expr_EQUALS_EQUALS_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr EQUALS_EQUALS expr");
    throw "generate_boolean_expr_EQUALS_EQUALS_expr not implemented";
}
ostream& generate_boolean_boolean_AMP_AMP_boolean(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean boolean AMP_AMP boolean");
    throw "generate_boolean_boolean_AMP_AMP_boolean not implemented";
}
ostream& generate_boolean_boolean_PIPE_PIPE_boolean(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean boolean PIPE_PIPE boolean");
    throw "generate_boolean_boolean_PIPE_PIPE_boolean not implemented";
}

// expr
ostream& generate_expr_term(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr term");
    throw "generate_expr_term not implemented";
}
ostream& generate_expr_expr_PLUS_term(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr expr PLUS term");
    throw "generate_expr_expr_PLUS_term not implemented";
}
ostream& generate_expr_expr_MINUS_term(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr expr MINUS term");
    throw "generate_expr_expr_MINUS_term not implemented";
}

// term
ostream& generate_term_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term factor");
    throw "generate_term_factor not implemented";
}
ostream& generate_term_term_STAR_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term STAR factor");
    throw "generate_term_term_STAR_factor not implemented";
}
ostream& generate_term_term_STAR_STAR_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term STAR_STAR factor");
    throw "generate_term_term_STAR_STAR_factor not implemented";
}
ostream& generate_term_term_SLASH_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term SLASH factor");
    throw "generate_term_term_SLASH_factor not implemented";
}
ostream& generate_term_term_SLASH_SLASH_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term SLASH_SLASH factor");
    throw "generate_term_term_SLASH_SLASH_factor not implemented";
}
ostream& generate_term_term_PCT_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term PCT factor");
    throw "generate_term_term_PCT_factor not implemented";
}
ostream& generate_term_term_AMP_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term AMP factor");
    throw "generate_term_term_AMP_factor not implemented";
}
ostream& generate_term_term_PIPE_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term PIPE factor");
    throw "generate_term_term_PIPE_factor not implemented";
}

// factor
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

// arglist
ostream& generate_arglist_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "arglist expr");
    throw "generate_arglist_expr not implemented";
}
ostream& generate_arglist_expr_COMMA_arglist(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "arglist expr COMMA arglist");
    throw "generate_arglist_expr_COMMA_arglist not implemented";
}

// string
ostream& generate_string_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "string ID");
    throw "generate_string_ID not implemented";
}
ostream& generate_string_STR(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "string STR");
    throw "generate_string_STR not implemented";
}

// lvalue
ostream& generate_lvalue_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "lvalue ID");
    throw "generate_lvalue_ID not implemented";
}
ostream& generate_lvalue_STAR_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "lvalue STAR factor");
    throw "generate_lvalue_STAR_factor not implemented";
}
ostream& generate_lvalue_LPAREN_lvalue_RPAREN(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "lvalue LPAREN lvalue RPAREN");
    throw "generate_lvalue_LPAREN_lvalue_RPAREN not implemented";
}

map<string, GenerateFunction> generateMap = {
    {"globals include globals", generate_globals_include_globals},
    {"globals procedure globals", generate_globals_procedure_globals},
    {"include POUND INCLUDE LT ID GT", generate_include_POUND_INCLUDE_LT_ID_GT},
    {"include POUND INCLUDE QUOTE ID QUOTE", generate_include_POUND_INCLUDE_QUOTE_ID_QUOTE},
    {"procedure vtype ID LPAREN params RPAREN LBRACE statements RBRACE", generate_procedure_vtype_ID_LPAREN_params_RPAREN_LBRACE_statements_RBRACE},
    {"params dcl params", generate_params_dcl_params},
    {"dcl vtype ID", generate_dcl_vtype_ID},
    {"dcl vtype ID EQUALS expr", generate_dcl_vtype_ID_EQUALS_expr},
    {"vtype signedtype type", generate_vtype_signedtype_type},
    {"vtype signedtype type STAR", generate_vtype_signedtype_type_STAR},
    {"vtype signedtype type AMP", generate_vtype_signedtype_type_AMP},
    {"signedtype UNSIGNED", generate_signedtype_UNSIGNED},
    {"type BOOL", generate_type_BOOL},
    {"type INT", generate_type_INT},
    {"type LONG", generate_type_LONG},
    {"type LONG LONG", generate_type_LONG_LONG},
    {"type DOUBLE", generate_type_DOUBLE},
    {"type FLOAT", generate_type_FLOAT},
    {"type ID", generate_type_ID},
    {"type VOID", generate_type_VOID},
    {"statements statements statement", generate_statements_statements_statement},
    {"statement dcl SEMICOLON", generate_statement_dcl_SEMICOLON},
    {"statement IF LPAREN boolean RPAREN LBRACE statements RBRACE elseifstatement elsestatement", generate_statement_IF_LPAREN_boolean_RPAREN_LBRACE_statements_RBRACE_elseifstatement_elsestatement},
    {"statement RETURN expr SEMICOLON", generate_statement_RETURN_expr_SEMICOLON},
    {"elseifstatement ELSE IF LPAREN boolean RPAREN LBRACE statements RBRACE elseifstatement", generate_elseifstatement_ELSE_IF_LPAREN_boolean_RPAREN_LBRACE_statements_RBRACE_elseifstatement},
    {"elsestatement ELSE LBRACE statements RBRACE", generate_elsestatement_ELSE_LBRACE_statements_RBRACE},
    {"boolean expr", generate_boolean_expr},
    {"boolean NOT expr", generate_boolean_NOT_expr},
    {"boolean expr GT expr", generate_boolean_expr_GT_expr},
    {"boolean expr GE expr", generate_boolean_expr_GE_expr},
    {"boolean expr LT expr", generate_boolean_expr_LT_expr},
    {"boolean expr LE expr", generate_boolean_expr_LE_expr},
    {"boolean expr NE expr", generate_boolean_expr_NE_expr},
    {"boolean expr EQUALS_EQUALS expr", generate_boolean_expr_EQUALS_EQUALS_expr},
    {"boolean boolean AMP_AMP boolean", generate_boolean_boolean_AMP_AMP_boolean},
    {"boolean boolean PIPE_PIPE boolean", generate_boolean_boolean_PIPE_PIPE_boolean},
    {"expr term", generate_expr_term},
    {"expr expr PLUS term", generate_expr_expr_PLUS_term},
    {"expr expr MINUS term", generate_expr_expr_MINUS_term},
    {"term factor", generate_term_factor},
    {"term term STAR factor", generate_term_term_STAR_factor},
    {"term term STAR_STAR factor", generate_term_term_STAR_STAR_factor},
    {"term term SLASH factor", generate_term_term_SLASH_factor},
    {"term term SLASH_SLASH factor", generate_term_term_SLASH_SLASH_factor},
    {"term term PCT factor", generate_term_term_PCT_factor},
    {"term term AMP factor", generate_term_term_AMP_factor},
    {"term term PIPE factor", generate_term_term_PIPE_factor},
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
    {"factor ID QUOTE string QUOTE", generate_factor_ID_QUOTE_string_QUOTE},
    {"arglist expr", generate_arglist_expr},
    {"arglist expr COMMA arglist", generate_arglist_expr_COMMA_arglist},
    {"string ID", generate_string_ID},
    {"string STR", generate_string_STR},
    {"lvalue ID", generate_lvalue_ID},
    {"lvalue STAR factor", generate_lvalue_STAR_factor},
    {"lvalue LPAREN lvalue RPAREN", generate_lvalue_LPAREN_lvalue_RPAREN}};

GenerateFunction getCodeGenerationFunction(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generateMap[nt->getRule()];
}
    