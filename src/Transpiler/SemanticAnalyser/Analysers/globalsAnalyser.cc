
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_globals_include_globals(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "globals include globals");
    throw "analyse_globals_include_globals not implemented";
}
ostream& analyse_globals_procedure_globals(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "globals procedure globals");
    throw "analyse_globals_procedure_globals not implemented";
}

map<string, AnalysisFunction> analyse_globals_map = {
    {"globals include globals", analyse_globals_include_globals},
    {"globals procedure globals", analyse_globals_procedure_globals}};

AnalysisFunction get_globals_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_globals_map[nt->getRule()];
}
        