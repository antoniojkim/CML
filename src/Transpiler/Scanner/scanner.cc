
#include "scanner.h"
#include <sstream>

using namespace std;
    
map<string, Type> keywordType = {
	{"if", IF},
	{"else", ELSE},
	{"while", WHILE},
	{"for", FOR},
	{"do", DO},
	{"return", RETURN},
	{"bool", BOOL},
	{"int", INT},
	{"float", FLOAT},
	{"double", DOUBLE},
	{"long", LONG},
	{"true", TRUE_},
	{"false", FALSE_},
	{"none", NONE_},
	{"NULL", NULL_},
	{"void", VOID},
	{"nullptr", NULLPTR},
	{"new", NEW},
	{"delete", DELETE},
	{"include", INCLUDE},
	{"unsigned", UNSIGNED},
	{"def", DEF}
};
map<Type, string> keywordLexeme = {
	{IF, "IF"},
	{ELSE, "ELSE"},
	{WHILE, "WHILE"},
	{FOR, "FOR"},
	{DO, "DO"},
	{RETURN, "RETURN"},
	{BOOL, "BOOL"},
	{INT, "INT"},
	{FLOAT, "FLOAT"},
	{DOUBLE, "DOUBLE"},
	{LONG, "LONG"},
	{TRUE_, "TRUE"},
	{FALSE_, "FALSE"},
	{NONE_, "NONE"},
	{NULL_, "NULL"},
	{VOID, "VOID"},
	{NULLPTR, "NULLPTR"},
	{NEW, "NEW"},
	{DELETE, "DELETE"},
	{INCLUDE, "INCLUDE"},
	{UNSIGNED, "UNSIGNED"},
	{DEF, "DEF"}
};
map<string, Type> tokenType = {
	{"(", LPAREN},
	{")", RPAREN},
	{"[", LSQUARE},
	{"]", RSQUARE},
	{"{", LBRACE},
	{"}", RBRACE},
	{"=", EQUALS},
	{"==", EQUALS_EQUALS},
	{"!=", NE},
	{"<", LT},
	{">", GT},
	{"<=", LE},
	{">=", GE},
	{"+", PLUS},
	{"-", MINUS},
	{"*", STAR},
	{"/", SLASH},
	{"%", PCT},
	{"^", CARET},
	{"&", AMP},
	{"|", PIPE},
	{"~", NEGATE},
	{"!", NOT},
	{"+=", PLUS_EQUALS},
	{"-=", MINUS_EQUALS},
	{"*=", STAR_EQUALS},
	{"/=", SLASH_EQUALS},
	{"%=", PCT_EQUALS},
	{"^=", CARET_EQUALS},
	{"&=", AMP_EQUALS},
	{"|=", PIPE_EQUALS},
	{"++", PLUS_PLUS},
	{"--", MINUS_MINUS},
	{"**", STAR_STAR},
	{"//", SLASH_SLASH},
	{"&&", AMP_AMP},
	{"<<", GT_GT},
	{"<-", L_ARROW},
	{"->", R_ARROW},
	{"||", PIPE_PIPE},
	{"::", COLON_COLON},
	{".", DOT},
	{",", COMMA},
	{":", COLON},
	{";", SEMICOLON},
	{"?", QUESTION},
	{"#", POUND},
	{"$", DOLLAR},
	{"\"", QUOTE},
	{"'", APOSTROPHE},
	{"\\", BACKSLASH},
	{"`", BACKTICK},
	{"_", UNDERSCORE},
	{"BOF", BOF_},
	{"EOF", EOF_}
};
map<Type, string> typeLexeme = {
	{LPAREN, "LPAREN"},
	{RPAREN, "RPAREN"},
	{LSQUARE, "LSQUARE"},
	{RSQUARE, "RSQUARE"},
	{LBRACE, "LBRACE"},
	{RBRACE, "RBRACE"},
	{EQUALS, "EQUALS"},
	{EQUALS_EQUALS, "EQUALS_EQUALS"},
	{NE, "NE"},
	{LT, "LT"},
	{GT, "GT"},
	{LE, "LE"},
	{GE, "GE"},
	{PLUS, "PLUS"},
	{MINUS, "MINUS"},
	{STAR, "STAR"},
	{SLASH, "SLASH"},
	{PCT, "PCT"},
	{CARET, "CARET"},
	{AMP, "AMP"},
	{PIPE, "PIPE"},
	{NEGATE, "NEGATE"},
	{NOT, "NOT"},
	{PLUS_EQUALS, "PLUS_EQUALS"},
	{MINUS_EQUALS, "MINUS_EQUALS"},
	{STAR_EQUALS, "STAR_EQUALS"},
	{SLASH_EQUALS, "SLASH_EQUALS"},
	{PCT_EQUALS, "PCT_EQUALS"},
	{CARET_EQUALS, "CARET_EQUALS"},
	{AMP_EQUALS, "AMP_EQUALS"},
	{PIPE_EQUALS, "PIPE_EQUALS"},
	{PLUS_PLUS, "PLUS_PLUS"},
	{MINUS_MINUS, "MINUS_MINUS"},
	{STAR_STAR, "STAR_STAR"},
	{SLASH_SLASH, "SLASH_SLASH"},
	{AMP_AMP, "AMP_AMP"},
	{GT_GT, "GT_GT"},
	{L_ARROW, "L_ARROW"},
	{R_ARROW, "R_ARROW"},
	{PIPE_PIPE, "PIPE_PIPE"},
	{COLON_COLON, "COLON_COLON"},
	{DOT, "DOT"},
	{COMMA, "COMMA"},
	{COLON, "COLON"},
	{SEMICOLON, "SEMICOLON"},
	{QUESTION, "QUESTION"},
	{POUND, "POUND"},
	{DOLLAR, "DOLLAR"},
	{QUOTE, "QUOTE"},
	{APOSTROPHE, "APOSTROPHE"},
	{BACKSLASH, "BACKSLASH"},
	{BACKTICK, "BACKTICK"},
	{UNDERSCORE, "UNDERSCORE"},
	{BOF_, "BOF_"},
	{EOF_, "EOF_"}
};
map<char, Type> charType = {
	{'(', LPAREN},
	{')', RPAREN},
	{'[', LSQUARE},
	{']', RSQUARE},
	{'{', LBRACE},
	{'}', RBRACE},
	{'=', EQUALS},
	{'<', LT},
	{'>', GT},
	{'+', PLUS},
	{'-', MINUS},
	{'*', STAR},
	{'/', SLASH},
	{'%', PCT},
	{'^', CARET},
	{'&', AMP},
	{'|', PIPE},
	{'~', NEGATE},
	{'!', NOT},
	{'.', DOT},
	{',', COMMA},
	{':', COLON},
	{';', SEMICOLON},
	{'?', QUESTION},
	{'#', POUND},
	{'$', DOLLAR},
	{'\"', QUOTE},
	{'\'', APOSTROPHE},
	{'`', BACKTICK},
	{'_', UNDERSCORE}
};

Type getType(char c) {
    if ('0' <= c && c <= '9')  return NUM;
    if ('a' <= c && c <= 'z')  return ID;
    if ('A' <= c && c <= 'Z')  return ID;
    if (charType.count(c) > 0) return charType[c];

    switch(c){
        case ' ':
            return WHITESPACE;
        case '\t':
            return WHITESPACE;
        case '\n':
            return WHITESPACE;
        case '\r':
            return WHITESPACE;
        default:
            return NONE;
    }
}

std::string getTypeString(const Type& type) {
    if (keywordLexeme.count(type) > 0) return keywordLexeme[type];
    if (typeLexeme.count(type) > 0)    return typeLexeme[type];
    if (type == ID)                    return "ID";
    if (type == STR)                   return "STR";
    if (type == NUM)                   return "NUM";
    if (type == WHITESPACE)            return "WHITESPACE";

    return "NONE";
} 

void scan(const std::string& str, std::list<Token>& tokens) {
    istringstream iss{str};
    scan(iss, tokens);
}
    
void scan(std::istream& in, std::list<Token>& tokens) {
    char c;
    ostringstream token;
    bool openQuote = false;
    Type current = NONE;
    while (in.get(c)) {
        Type type = getType(c);
        // cout << token.str() << " " << getTypeString(current) << "    " << c << " " << getTypeString(type) << endl;
        if (current == NONE || current == type) {
            current = type;
        } else if ((current == ID && (type == NUM || type == UNDERSCORE)) ||
                   (current == UNDERSCORE && (type == ID || type == NUM))) {
            current = ID;
        } else if ((current == NUM && type == DOT) || 
                   (current == NUM && type == ID && (c == 'e' || c == 'E'))) {
            current = NUM;
        } else if (openQuote && 
                    ((current == STR && type == ID) ||
                     (current == NUM && type == ID) ||
                     (current == ID && type == WHITESPACE) ||
                     (current == STR && type == WHITESPACE))) {
            current = STR;
    
        } else if (current == EQUALS && type == EQUALS) { /*  ==  */
            current = EQUALS_EQUALS;
        } else if (current == NOT && type == EQUALS) { /*  !=  */
            current = NE;
        } else if (current == LT && type == EQUALS) { /*  <=  */
            current = LE;
        } else if (current == GT && type == EQUALS) { /*  >=  */
            current = GE;
        } else if (current == PLUS && type == EQUALS) { /*  +=  */
            current = PLUS_EQUALS;
        } else if (current == MINUS && type == EQUALS) { /*  -=  */
            current = MINUS_EQUALS;
        } else if (current == STAR && type == EQUALS) { /*  *=  */
            current = STAR_EQUALS;
        } else if (current == SLASH && type == EQUALS) { /*  /=  */
            current = SLASH_EQUALS;
        } else if (current == PCT && type == EQUALS) { /*  %=  */
            current = PCT_EQUALS;
        } else if (current == CARET && type == EQUALS) { /*  ^=  */
            current = CARET_EQUALS;
        } else if (current == AMP && type == EQUALS) { /*  &=  */
            current = AMP_EQUALS;
        } else if (current == PIPE && type == EQUALS) { /*  |=  */
            current = PIPE_EQUALS;
        } else if (current == PLUS && type == PLUS) { /*  ++  */
            current = PLUS_PLUS;
        } else if (current == MINUS && type == MINUS) { /*  --  */
            current = MINUS_MINUS;
        } else if (current == STAR && type == STAR) { /*  **  */
            current = STAR_STAR;
        } else if (current == SLASH && type == SLASH) { /*  //  */
            current = SLASH_SLASH;
        } else if (current == AMP && type == AMP) { /*  &&  */
            current = AMP_AMP;
        } else if (current == LT && type == LT) { /*  <<  */
            current = GT_GT;
        } else if (current == LT && type == MINUS) { /*  <-  */
            current = L_ARROW;
        } else if (current == MINUS && type == GT) { /*  ->  */
            current = R_ARROW;
        } else if (current == PIPE && type == PIPE) { /*  ||  */
            current = PIPE_PIPE;
        } else if (current == COLON && type == COLON) { /*  ::  */
            current = COLON_COLON;

        } else {
            if (!token.str().empty() && current != WHITESPACE) {
                auto str = token.str();
                if (current == ID && keywordType.count(str) > 0){
                    tokens.emplace_back(Token{str, keywordType[str]});
                } else {
                    tokens.emplace_back(Token{str, current});
                }
                if (current == QUOTE){
                    openQuote = !openQuote;
                }
                token = ostringstream();
            }
            current = type;
        }
        if (current != WHITESPACE){
            token << c;
        }
    }
    if (!token.str().empty()) {
        tokens.emplace_back(Token{token.str(), current});
    }
}



ostream& print(ostream& out, list<Token> tokens, const string& delimiter, const bool& printType) {
    bool first = true;
    for (auto& token : tokens) {
        if (first) {
            first = false;
        } else {
            out << delimiter;
        }
        out << token.lexeme;
        if (printType){
            out << "  " << getTypeString(token.type);
        }
    }
    return out;
}
    