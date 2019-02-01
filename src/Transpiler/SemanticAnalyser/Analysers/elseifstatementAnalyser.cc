
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_elseifstatement_ELSE_IF_LPAREN_expr_RPAREN_LBRACE_statements_RBRACE_elseifstatement(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "elseifstatement ELSE IF LPAREN expr RPAREN LBRACE statements RBRACE elseifstatement");
    throw "analyse_elseifstatement_ELSE_IF_LPAREN_expr_RPAREN_LBRACE_statements_RBRACE_elseifstatement not implemented";
}

map<string, AnalysisFunction> analyse_elseifstatement_map = {
    {"elseifstatement ELSE IF LPAREN expr RPAREN LBRACE statements RBRACE elseifstatement", analyse_elseifstatement_ELSE_IF_LPAREN_expr_RPAREN_LBRACE_statements_RBRACE_elseifstatement}};

AnalysisFunction get_elseifstatement_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_elseifstatement_map[nt->getRule()];
}
        