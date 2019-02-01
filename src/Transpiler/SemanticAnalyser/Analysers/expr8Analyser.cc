
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_expr8_expr7(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "expr8 expr7");
    throw "analyse_expr8_expr7 not implemented";
}

map<string, AnalysisFunction> analyse_expr8_map = {
    {"expr8 expr7", analyse_expr8_expr7}};

AnalysisFunction get_expr8_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_expr8_map[nt->getRule()];
}
        