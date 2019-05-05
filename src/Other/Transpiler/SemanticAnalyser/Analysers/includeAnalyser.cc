
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

void analyse_include_POUND_INCLUDE_LT_ID_GT(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "include POUND INCLUDE LT ID GT");
    throw "analyse_include_POUND_INCLUDE_LT_ID_GT not implemented";
}
void analyse_include_POUND_INCLUDE_QUOTE_ID_QUOTE(ContextSensitiveTree* tree, const string& indent){
    assert(tree->getParams()->rule == "include POUND INCLUDE QUOTE ID QUOTE");
    throw "analyse_include_POUND_INCLUDE_QUOTE_ID_QUOTE not implemented";
}

map<string, AnalysisFunction> analyse_include_map = {
    {"include POUND INCLUDE LT ID GT", analyse_include_POUND_INCLUDE_LT_ID_GT},
    {"include POUND INCLUDE QUOTE ID QUOTE", analyse_include_POUND_INCLUDE_QUOTE_ID_QUOTE}};

AnalysisFunction get_include_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_include_map[nt->getRule()];
}
        