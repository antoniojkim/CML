
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_statements_statements_statement(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "statements statements statement");
    throw "generate_statements_statements_statement not implemented";
}

map<string, GenerateFunction> generate_statements_map = {
    {"statements statements statement", generate_statements_statements_statement}};

GenerateFunction get_statements_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_statements_map[nt->getRule()];
}
        