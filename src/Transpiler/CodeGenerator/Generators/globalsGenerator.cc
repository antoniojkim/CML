
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_globals_include_globals(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "globals include globals");
    throw "generate_globals_include_globals not implemented";
}
ostream& generate_globals_procedure_globals(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "globals procedure globals");
    throw "generate_globals_procedure_globals not implemented";
}

map<string, GenerateFunction> generate_globals_map = {
    {"globals include globals", generate_globals_include_globals},
    {"globals procedure globals", generate_globals_procedure_globals}};

GenerateFunction get_globals_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_globals_map[nt->getRule()];
}
        