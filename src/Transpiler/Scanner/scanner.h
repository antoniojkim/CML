
#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <map>
    
enum Type {
	ID,
	STR,
	NUM,
	LPAREN,
	RPAREN,
	LSQUARE,
	RSQUARE,
	LBRACE,
	RBRACE,
	EQUALS,
	EQUALS_EQUALS,
	NE,
	QE,
	LT,
	GT,
	LE,
	GE,
	PLUS,
	MINUS,
	STAR,
	SLASH,
	PCT,
	CARET,
	AMP,
	PIPE,
	TILDE,
	EXCL,
	PLUS_EQUALS,
	MINUS_EQUALS,
	STAR_EQUALS,
	SLASH_EQUALS,
	PCT_EQUALS,
	CARET_EQUALS,
	AMP_EQUALS,
	PIPE_EQUALS,
	GT_GT_EQUALS,
	LT_LT_EQUALS,
	PLUS_PLUS,
	MINUS_MINUS,
	STAR_STAR,
	SLASH_SLASH,
	AMP_AMP,
	LT_LT,
	GT_GT,
	L_ARROW,
	R_ARROW,
	PIPE_PIPE,
	COLON_COLON,
	DOT,
	COMMA,
	COLON,
	SEMICOLON,
	QUESTION,
	POUND,
	DOLLAR,
	QUOTE,
	APOSTROPHE,
	BACKSLASH,
	BACKTICK,
	UNDERSCORE,
	BOF_,
	EOF_,
	IF,
	ELSE,
	WHILE,
	FOR,
	DO,
	RETURN,
	BOOL,
	INT,
	FLOAT,
	DOUBLE,
	LONG,
	TRUE_,
	FALSE_,
	NONE_,
	NULL_,
	VOID,
	NULLPTR,
	NEW,
	DELETE,
	INCLUDE,
	UNSIGNED,
	DEF,
	WHITESPACE,
	NONE
};

Type getType(char c);
std::string getTypeString(const Type& type);

struct Token {
    std::string lexeme;
    Type type;
};

void scan(const std::string& str, std::list<Token>& tokens);
void scan(std::istream& in, std::list<Token>& tokens);

std::ostream& print(std::ostream& out, std::list<Token> tokens, const std::string& delimiter="", const bool& printType=false);

#endif
    