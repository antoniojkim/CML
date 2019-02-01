
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_statement_dcl_SEMICOLON(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "statement dcl SEMICOLON");
    throw "analyse_statement_dcl_SEMICOLON not implemented";
}
ostream& analyse_statement_IF_LPAREN_expr_RPAREN_LBRACE_statements_RBRACE_elseifstatement_elsestatement(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "statement IF LPAREN expr RPAREN LBRACE statements RBRACE elseifstatement elsestatement");
    throw "analyse_statement_IF_LPAREN_expr_RPAREN_LBRACE_statements_RBRACE_elseifstatement_elsestatement not implemented";
}
ostream& analyse_statement_RETURN_expr_SEMICOLON(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "statement RETURN expr SEMICOLON");
    throw "analyse_statement_RETURN_expr_SEMICOLON not implemented";
}

map<string, AnalysisFunction> analyse_statement_map = {
    {"statement dcl SEMICOLON", analyse_statement_dcl_SEMICOLON},
    {"statement IF LPAREN expr RPAREN LBRACE statements RBRACE elseifstatement elsestatement", analyse_statement_IF_LPAREN_expr_RPAREN_LBRACE_statements_RBRACE_elseifstatement_elsestatement},
    {"statement RETURN expr SEMICOLON", analyse_statement_RETURN_expr_SEMICOLON}};

AnalysisFunction get_statement_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_statement_map[nt->getRule()];
}
        