
#ifndef SEMANTIC_ANALYSIS_H
#define SEMANTIC_ANALYSIS_H

#include <iostream>
#include <string>
#include "../ContextSensitiveTrees/ContextSensitiveTrees.h"
#include "../Parser/parsetree.h"

typedef void (*AnalysisFunction)(ContextSensitiveTree* tree, const std::string& indent);
typedef AnalysisFunction (*GetAnalysisFunction)(ParseTree* tree);

AnalysisFunction getSemanticAnalysisFunction(ParseTree* tree);
    
AnalysisFunction get_globals_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_include_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_procedure_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_params_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_dcl_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_vtype_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_signedtype_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_type_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_statements_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_statement_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_elseifstatement_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_elsestatement_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr1_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr2_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr3_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr4_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr5_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr6_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr7_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr8_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr9_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr10_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr11_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr12_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr13_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr14_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr15_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_expr16_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_factor_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_arglist_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_string_semantic_analysis_function(ParseTree* tree);
AnalysisFunction get_lvalue_semantic_analysis_function(ParseTree* tree);


#endif // SEMANTIC_ANALYSIS_H
    
