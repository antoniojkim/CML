
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_string_ID(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "string ID");
    throw "analyse_string_ID not implemented";
}
void analyse_string_STR(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "string STR");
    throw "analyse_string_STR not implemented";
}

map<string, AnalysisFunction> analyse_string_map = {
    {"string ID", analyse_string_ID},
    {"string STR", analyse_string_STR}};

AnalysisFunction get_string_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_string_map[nt->getRule()];
}
        