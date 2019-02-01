
#include "./semanticAnalyser.h"
#include <map>

using namespace std;
    

map<string, GetAnalysisFunction> analysisFunctionsMap = {
    {"globals", get_globals_semantic_analysis_function},
    {"include", get_include_semantic_analysis_function},
    {"procedure", get_procedure_semantic_analysis_function},
    {"params", get_params_semantic_analysis_function},
    {"dcl", get_dcl_semantic_analysis_function},
    {"vtype", get_vtype_semantic_analysis_function},
    {"signedtype", get_signedtype_semantic_analysis_function},
    {"type", get_type_semantic_analysis_function},
    {"statements", get_statements_semantic_analysis_function},
    {"statement", get_statement_semantic_analysis_function},
    {"elseifstatement", get_elseifstatement_semantic_analysis_function},
    {"elsestatement", get_elsestatement_semantic_analysis_function},
    {"expr", get_expr_semantic_analysis_function},
    {"expr1", get_expr1_semantic_analysis_function},
    {"expr2", get_expr2_semantic_analysis_function},
    {"expr3", get_expr3_semantic_analysis_function},
    {"expr4", get_expr4_semantic_analysis_function},
    {"expr5", get_expr5_semantic_analysis_function},
    {"expr6", get_expr6_semantic_analysis_function},
    {"expr7", get_expr7_semantic_analysis_function},
    {"expr8", get_expr8_semantic_analysis_function},
    {"expr9", get_expr9_semantic_analysis_function},
    {"expr10", get_expr10_semantic_analysis_function},
    {"expr11", get_expr11_semantic_analysis_function},
    {"expr12", get_expr12_semantic_analysis_function},
    {"expr13", get_expr13_semantic_analysis_function},
    {"expr14", get_expr14_semantic_analysis_function},
    {"expr15", get_expr15_semantic_analysis_function},
    {"expr16", get_expr16_semantic_analysis_function},
    {"factor", get_factor_semantic_analysis_function},
    {"arglist", get_arglist_semantic_analysis_function},
    {"string", get_string_semantic_analysis_function},
    {"lvalue", get_lvalue_semantic_analysis_function}};

GenerateFunction getSemanticAnalysisFunction(ParseTree* tree){
    return analysisFunctionsMap[tree->getRoot()](tree);
}
    