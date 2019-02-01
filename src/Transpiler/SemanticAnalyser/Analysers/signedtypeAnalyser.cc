
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_signedtype_UNSIGNED(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "signedtype UNSIGNED");
    throw "analyse_signedtype_UNSIGNED not implemented";
}

map<string, AnalysisFunction> analyse_signedtype_map = {
    {"signedtype UNSIGNED", analyse_signedtype_UNSIGNED}};

AnalysisFunction get_signedtype_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_signedtype_map[nt->getRule()];
}
        