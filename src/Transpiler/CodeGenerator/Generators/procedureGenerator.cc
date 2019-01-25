
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_procedure_vtype_ID_LPAREN_params_RPAREN_LBRACE_statements_RBRACE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "procedure vtype ID LPAREN params RPAREN LBRACE statements RBRACE");
    throw "generate_procedure_vtype_ID_LPAREN_params_RPAREN_LBRACE_statements_RBRACE not implemented";
}

map<string, GenerateFunction> generate_procedure_map = {
    {"procedure vtype ID LPAREN params RPAREN LBRACE statements RBRACE", generate_procedure_vtype_ID_LPAREN_params_RPAREN_LBRACE_statements_RBRACE}};

GenerateFunction get_procedure_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_procedure_map[nt->getRule()];
}
        