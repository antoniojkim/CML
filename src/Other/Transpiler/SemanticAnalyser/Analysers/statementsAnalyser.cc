
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_statements_statements_statement(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "statements statements statement");
    throw "analyse_statements_statements_statement not implemented";
}

map<string, AnalysisFunction> analyse_statements_map = {
    {"statements statements statement", analyse_statements_statements_statement}};

AnalysisFunction get_statements_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_statements_map[nt->getRule()];
}
        