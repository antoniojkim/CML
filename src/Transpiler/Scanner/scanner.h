
#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <list>
#include <string>
#include <map>
    
enum Type {
	ID,
	STR,
	NUM,
	LPAREN,
	RPAREN,
	LSQUARE,
	RSQUARE,
	LCURLY,
	RCURLY,
	EQUALS,
	EQUALS_EQUALS,
	NE,
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
	NEGATE,
	NOT,
	PLUS_EQUALS,
	MINUS_EQUALS,
	STAR_EQUALS,
	SLASH_EQUALS,
	PCT_EQUALS,
	CARET_EQUALS,
	AMP_EQUALS,
	PIPE_EQUALS,
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
	IF,
	ELSE,
	WHILE,
	FOR,
	DO,
	RETURN,
	INT,
	FLOAT,
	DOUBLE,
	LONG,
	STRING,
	NONE_,
	NULL_,
	NULLPTR,
	NEW,
	DELETE,
	INCLUDE,
	DEF,
	WHITESPACE,
	NONE
};
extern std::map<std::string, Type> keywords;
extern std::map<std::string, Type> charType;

Type getType(char c);
std::string getTypeString(Type type);

struct Token {
    std::string lexeme;
    Type type;
};

void scan(const std::string& str, std::list<Token>& tokens);
void scan(std::istream& in, std::list<Token>& tokens);

#endif
    