
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_boolean_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr");
    throw "generate_boolean_expr not implemented";
}
ostream& generate_boolean_NOT_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean NOT expr");
    throw "generate_boolean_NOT_expr not implemented";
}
ostream& generate_boolean_expr_GT_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr GT expr");
    throw "generate_boolean_expr_GT_expr not implemented";
}
ostream& generate_boolean_expr_GE_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr GE expr");
    throw "generate_boolean_expr_GE_expr not implemented";
}
ostream& generate_boolean_expr_LT_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr LT expr");
    throw "generate_boolean_expr_LT_expr not implemented";
}
ostream& generate_boolean_expr_LE_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr LE expr");
    throw "generate_boolean_expr_LE_expr not implemented";
}
ostream& generate_boolean_expr_NE_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr NE expr");
    throw "generate_boolean_expr_NE_expr not implemented";
}
ostream& generate_boolean_expr_EQUALS_EQUALS_expr(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean expr EQUALS_EQUALS expr");
    throw "generate_boolean_expr_EQUALS_EQUALS_expr not implemented";
}
ostream& generate_boolean_boolean_AMP_AMP_boolean(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean boolean AMP_AMP boolean");
    throw "generate_boolean_boolean_AMP_AMP_boolean not implemented";
}
ostream& generate_boolean_boolean_PIPE_PIPE_boolean(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "boolean boolean PIPE_PIPE boolean");
    throw "generate_boolean_boolean_PIPE_PIPE_boolean not implemented";
}

map<string, GenerateFunction> generate_boolean_map = {
    {"boolean expr", generate_boolean_expr},
    {"boolean NOT expr", generate_boolean_NOT_expr},
    {"boolean expr GT expr", generate_boolean_expr_GT_expr},
    {"boolean expr GE expr", generate_boolean_expr_GE_expr},
    {"boolean expr LT expr", generate_boolean_expr_LT_expr},
    {"boolean expr LE expr", generate_boolean_expr_LE_expr},
    {"boolean expr NE expr", generate_boolean_expr_NE_expr},
    {"boolean expr EQUALS_EQUALS expr", generate_boolean_expr_EQUALS_EQUALS_expr},
    {"boolean boolean AMP_AMP boolean", generate_boolean_boolean_AMP_AMP_boolean},
    {"boolean boolean PIPE_PIPE boolean", generate_boolean_boolean_PIPE_PIPE_boolean}};

GenerateFunction get_boolean_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_boolean_map[nt->getRule()];
}
        