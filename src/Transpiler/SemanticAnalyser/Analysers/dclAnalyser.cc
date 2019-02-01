
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_dcl_vtype_ID(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "dcl vtype ID");
    throw "analyse_dcl_vtype_ID not implemented";
}
ostream& analyse_dcl_vtype_ID_EQUALS_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "dcl vtype ID EQUALS expr");
    throw "analyse_dcl_vtype_ID_EQUALS_expr not implemented";
}

map<string, AnalysisFunction> analyse_dcl_map = {
    {"dcl vtype ID", analyse_dcl_vtype_ID},
    {"dcl vtype ID EQUALS expr", analyse_dcl_vtype_ID_EQUALS_expr}};

AnalysisFunction get_dcl_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_dcl_map[nt->getRule()];
}
        