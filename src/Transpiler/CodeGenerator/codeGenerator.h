
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
GenerateFunction get_boolean_code_generation_function(ParseTree* tree);
GenerateFunction get_expr_code_generation_function(ParseTree* tree);
GenerateFunction get_term_code_generation_function(ParseTree* tree);
GenerateFunction get_factor_code_generation_function(ParseTree* tree);
GenerateFunction get_arglist_code_generation_function(ParseTree* tree);
GenerateFunction get_string_code_generation_function(ParseTree* tree);
GenerateFunction get_lvalue_code_generation_function(ParseTree* tree);


#endif // CODE_GENERATOR_H
    
