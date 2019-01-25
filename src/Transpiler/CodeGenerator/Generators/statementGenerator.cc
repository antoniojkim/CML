
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_statement_dcl_SEMICOLON(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "statement dcl SEMICOLON");
    throw "generate_statement_dcl_SEMICOLON not implemented";
}
ostream& generate_statement_IF_LPAREN_boolean_RPAREN_LBRACE_statements_RBRACE_elseifstatement_elsestatement(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "statement IF LPAREN boolean RPAREN LBRACE statements RBRACE elseifstatement elsestatement");
    throw "generate_statement_IF_LPAREN_boolean_RPAREN_LBRACE_statements_RBRACE_elseifstatement_elsestatement not implemented";
}
ostream& generate_statement_RETURN_expr_SEMICOLON(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "statement RETURN expr SEMICOLON");
    throw "generate_statement_RETURN_expr_SEMICOLON not implemented";
}

map<string, GenerateFunction> generate_statement_map = {
    {"statement dcl SEMICOLON", generate_statement_dcl_SEMICOLON},
    {"statement IF LPAREN boolean RPAREN LBRACE statements RBRACE elseifstatement elsestatement", generate_statement_IF_LPAREN_boolean_RPAREN_LBRACE_statements_RBRACE_elseifstatement_elsestatement},
    {"statement RETURN expr SEMICOLON", generate_statement_RETURN_expr_SEMICOLON}};

GenerateFunction get_statement_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_statement_map[nt->getRule()];
}
        