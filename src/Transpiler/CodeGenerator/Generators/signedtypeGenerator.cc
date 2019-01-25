
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_signedtype_UNSIGNED(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "signedtype UNSIGNED");
    throw "generate_signedtype_UNSIGNED not implemented";
}

map<string, GenerateFunction> generate_signedtype_map = {
    {"signedtype UNSIGNED", generate_signedtype_UNSIGNED}};

GenerateFunction get_signedtype_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_signedtype_map[nt->getRule()];
}
        