
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_params_dcl_params(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "params dcl params");
    throw "analyse_params_dcl_params not implemented";
}

map<string, AnalysisFunction> analyse_params_map = {
    {"params dcl params", analyse_params_dcl_params}};

AnalysisFunction get_params_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_params_map[nt->getRule()];
}
        