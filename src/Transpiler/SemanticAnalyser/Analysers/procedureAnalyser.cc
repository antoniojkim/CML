
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;

ostream& analyse_procedure_vtype_ID_LPAREN_params_RPAREN_LBRACE_statements_RBRACE(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "procedure vtype ID LPAREN params RPAREN LBRACE statements RBRACE");
    throw "analyse_procedure_vtype_ID_LPAREN_params_RPAREN_LBRACE_statements_RBRACE not implemented";
}

map<string, AnalysisFunction> analyse_procedure_map = {
    {"procedure vtype ID LPAREN params RPAREN LBRACE statements RBRACE", analyse_procedure_vtype_ID_LPAREN_params_RPAREN_LBRACE_statements_RBRACE}};

AnalysisFunction get_procedure_semantic_analysis_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_procedure_map[nt->getRule()];
}
        