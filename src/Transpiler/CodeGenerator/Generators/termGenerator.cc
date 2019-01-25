
#include "../codeGenerator.h"
#include <cassert>

using namespace std;

ostream& generate_term_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term factor");
    throw "generate_term_factor not implemented";
}
ostream& generate_term_term_STAR_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term STAR factor");
    throw "generate_term_term_STAR_factor not implemented";
}
ostream& generate_term_term_STAR_STAR_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term STAR_STAR factor");
    throw "generate_term_term_STAR_STAR_factor not implemented";
}
ostream& generate_term_term_SLASH_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term SLASH factor");
    throw "generate_term_term_SLASH_factor not implemented";
}
ostream& generate_term_term_SLASH_SLASH_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term SLASH_SLASH factor");
    throw "generate_term_term_SLASH_SLASH_factor not implemented";
}
ostream& generate_term_term_PCT_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term PCT factor");
    throw "generate_term_term_PCT_factor not implemented";
}
ostream& generate_term_term_AMP_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term AMP factor");
    throw "generate_term_term_AMP_factor not implemented";
}
ostream& generate_term_term_PIPE_factor(ContextSensitiveTree* tree, ostream& out, const string& indent){
    assert(tree->getParams()->rule == "term term PIPE factor");
    throw "generate_term_term_PIPE_factor not implemented";
}

map<string, GenerateFunction> generate_term_map = {
    {"term factor", generate_term_factor},
    {"term term STAR factor", generate_term_term_STAR_factor},
    {"term term STAR_STAR factor", generate_term_term_STAR_STAR_factor},
    {"term term SLASH factor", generate_term_term_SLASH_factor},
    {"term term SLASH_SLASH factor", generate_term_term_SLASH_SLASH_factor},
    {"term term PCT factor", generate_term_term_PCT_factor},
    {"term term AMP factor", generate_term_term_AMP_factor},
    {"term term PIPE factor", generate_term_term_PIPE_factor}};

GenerateFunction get_term_code_generation_function(ParseTree* tree){
    NonTerminal* nt = tree->getNonTerminal();
    return generate_term_map[nt->getRule()];
}
        