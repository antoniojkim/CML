
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
    {"expr", get_expr_code_generation_function},
    {"expr1", get_expr1_code_generation_function},
    {"expr2", get_expr2_code_generation_function},
    {"expr3", get_expr3_code_generation_function},
    {"expr4", get_expr4_code_generation_function},
    {"expr5", get_expr5_code_generation_function},
    {"expr6", get_expr6_code_generation_function},
    {"expr7", get_expr7_code_generation_function},
    {"expr8", get_expr8_code_generation_function},
    {"expr9", get_expr9_code_generation_function},
    {"expr10", get_expr10_code_generation_function},
    {"expr11", get_expr11_code_generation_function},
    {"expr12", get_expr12_code_generation_function},
    {"expr13", get_expr13_code_generation_function},
    {"expr14", get_expr14_code_generation_function},
    {"expr15", get_expr15_code_generation_function},
    {"expr16", get_expr16_code_generation_function},
    {"factor", get_factor_code_generation_function},
    {"arglist", get_arglist_code_generation_function},
    {"string", get_string_code_generation_function},
    {"lvalue", get_lvalue_code_generation_function}};

GenerateFunction getCodeGenerationFunction(ParseTree* tree){
    return generateFunctionsMap[tree->getRoot()](tree);
}
    