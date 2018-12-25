#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <list>
#include <string>

enum Type {
    INT,
    FLOAT,
    EQUALS,
    LESS_THAN,
    GREATER_THAN,
    PLUS,
    MINUS,
    STAR,
    AMP,
    MOD,
    CARET,
    SLASH,
    BACKSLASH,
    PIPE,
    STR,
    QUOTE,
    APOSTROPHE,
    LPAREN,
    RPAREN,
    LSQUARE,
    RSQUARE,
    LCURLY,
    RCURLY,
    DOT,
    COMMA,
    COLON,
    SEMICOLON,
    QUESTION,
    UNDERSCORE,
    NEGATE,
    BACKTICK,
    PLUS_EQUALS,
    MINUS_EQUALS,
    STAR_EQUALS,
    SLASH_EQUALS,
    MOD_EQUALS,
    CARET_EQUALS,
    EQUALS_EQUALS,
    PLUS_PLUS,
    MINUS_MINUS,
    STAR_STAR,
    SLASH_SLASH,
    BOOLEAN_AND,
    BOOLEAN_OR,
    L_ARROW,
    R_ARROW,
    // SQRT,
    // CBRT,
    WHITESPACE,
    NONE
};

Type getType(char c);
std::string getTypeString(Type type);

struct Token {
    std::string lexeme;
    Type type;
};

void scan(const std::string& str, std::list<Token>& tokens);
void scan(std::istream& in, std::list<Token>& tokens);

#endif
