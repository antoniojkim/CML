
#include "./codeGenerator.h"
#include <map>

using namespace std;
    

map<string, GetGenerateFunction> generateFunctionsMap = {
    {"globals", get_globals_code_generation_function},
    {"include", get_include_code_generation_function},
    {"procedure", get_procedure_code_generation_function},
    {"params", get_params_code_generation_function},
    {"dcl", get_dcl_code_generation_function},
    {"vtype", get_vtype_code_generation_function},
    {"signedtype", get_signedtype_code_generation_function},
    {"type", get_type_code_generation_function},
    {"statements", get_statements_code_generation_function},
    {"statement", get_statement_code_generation_function},
    {"elseifstatement", get_elseifstatement_code_generation_function},
    {"elsestatement", get_elsestatement_code_generation_function},
    {"boolean", get_boolean_code_generation_function},
    {"expr", get_expr_code_generation_function},
    {"term", get_term_code_generation_function},
    {"factor", get_factor_code_generation_function},
    {"arglist", get_arglist_code_generation_function},
    {"string", get_string_code_generation_function},
    {"lvalue", get_lvalue_code_generation_function}};

GenerateFunction getCodeGenerationFunction(ParseTree* tree){
    return generateFunctionsMap[tree->getRoot()](tree);
}
    