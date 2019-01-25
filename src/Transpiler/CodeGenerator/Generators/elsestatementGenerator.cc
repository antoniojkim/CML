
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_elsestatement_ELSE_LBRACE_statements_RBRACE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "elsestatement ELSE LBRACE statements RBRACE");
    throw "generate_elsestatement_ELSE_LBRACE_statements_RBRACE not implemented";
}

map<string, GenerateFunction> generate_elsestatement_map = {
    {"elsestatement ELSE LBRACE statements RBRACE", generate_elsestatement_ELSE_LBRACE_statements_RBRACE}};

GenerateFunction get_elsestatement_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_elsestatement_map[nt->getRule()];
}
        