
#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <iostream>
#include <string>
#include "../ContextSensitiveTrees/ContextSensitiveTrees.h"
#include "../Parser/parsetree.h"

typedef std::ostream& (*GenerateFunction)(ContextSensitiveTree* tree, std::ostream& out, const std::string& indent);
typedef GenerateFunction (*GetGenerateFunction)(ParseTree* tree);

GenerateFunction getCodeGenerationFunction(ParseTree* tree);
    
GenerateFunction get_globals_code_generation_function(ParseTree* tree);
GenerateFunction get_include_code_generation_function(ParseTree* tree);
GenerateFunction get_procedure_code_generation_function(ParseTree* tree);
GenerateFunction get_params_code_generation_function(ParseTree* tree);
GenerateFunction get_dcl_code_generation_function(ParseTree* tree);
GenerateFunction get_vtype_code_generation_function(ParseTree* tree);
GenerateFunction get_signedtype_code_generation_function(ParseTree* tree);
GenerateFunction get_type_code_generation_function(ParseTree* tree);
GenerateFunction get_statements_code_generation_function(ParseTree* tree);
GenerateFunction get_statement_code_generation_function(ParseTree* tree);
GenerateFunction get_elseifstatement_code_generation_function(ParseTree* tree);
GenerateFunction get_elsestatement_code_generation_function(ParseTree* tree);
GenerateFunction get_expr_code_generation_function(ParseTree* tree);
GenerateFunction get_expr1_code_generation_function(ParseTree* tree);
GenerateFunction get_expr2_code_generation_function(ParseTree* tree);
GenerateFunction get_expr3_code_generation_function(ParseTree* tree);
GenerateFunction get_expr4_code_generation_function(ParseTree* tree);
GenerateFunction get_expr5_code_generation_function(ParseTree* tree);
GenerateFunction get_expr6_code_generation_function(ParseTree* tree);
GenerateFunction get_expr7_code_generation_function(ParseTree* tree);
GenerateFunction get_expr8_code_generation_function(ParseTree* tree);
GenerateFunction get_expr9_code_generation_function(ParseTree* tree);
GenerateFunction get_expr10_code_generation_function(ParseTree* tree);
GenerateFunction get_expr11_code_generation_function(ParseTree* tree);
GenerateFunction get_expr12_code_generation_function(ParseTree* tree);
GenerateFunction get_expr13_code_generation_function(ParseTree* tree);
GenerateFunction get_expr14_code_generation_function(ParseTree* tree);
GenerateFunction get_expr15_code_generation_function(ParseTree* tree);
GenerateFunction get_expr16_code_generation_function(ParseTree* tree);
GenerateFunction get_factor_code_generation_function(ParseTree* tree);
GenerateFunction get_arglist_code_generation_function(ParseTree* tree);
GenerateFunction get_string_code_generation_function(ParseTree* tree);
GenerateFunction get_lvalue_code_generation_function(ParseTree* tree);


#endif // CODE_GENERATOR_H
    
