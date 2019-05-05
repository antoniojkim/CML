
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_elseifstatement_ELSE_IF_LPAREN_expr_RPAREN_LBRACE_statements_RBRACE_elseifstatement(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "elseifstatement ELSE IF LPAREN expr RPAREN LBRACE statements RBRACE elseifstatement");
    throw "generate_elseifstatement_ELSE_IF_LPAREN_expr_RPAREN_LBRACE_statements_RBRACE_elseifstatement not implemented";
}

map<string, GenerateFunction> generate_elseifstatement_map = {
    {"elseifstatement ELSE IF LPAREN expr RPAREN LBRACE statements RBRACE elseifstatement", generate_elseifstatement_ELSE_IF_LPAREN_expr_RPAREN_LBRACE_statements_RBRACE_elseifstatement}};

GenerateFunction get_elseifstatement_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_elseifstatement_map[nt->getRule()];
}
        