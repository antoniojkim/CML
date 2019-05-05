
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_elsestatement_ELSE_LBRACE_statements_RBRACE(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "elsestatement ELSE LBRACE statements RBRACE");
    throw "analyse_elsestatement_ELSE_LBRACE_statements_RBRACE not implemented";
}

map<string, AnalysisFunction> analyse_elsestatement_map = {
    {"elsestatement ELSE LBRACE statements RBRACE", analyse_elsestatement_ELSE_LBRACE_statements_RBRACE}};

AnalysisFunction get_elsestatement_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_elsestatement_map[nt->getRule()];
}
        