
#include "scanner.h"
#include <sstream>

using namespace std;

Type getType(char c) {
    if ('0' <= c && c <= '9') return NUM;
    if ('a' <= c && c <= 'z') return STR;
    if ('A' <= c && c <= 'Z') return STR;

    switch (c) {
        case '=':
            return EQUALS;
        case '<':
            return LESS_THAN;
        case '>':
            return GREATER_THAN;
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '*':
            return STAR;
        case '%':
            return PCT;
        case '^':
            return CARET;
        case '/':
            return SLASH;
        case '\\':
            return BACKSLASH;
        case '|':
            return PIPE;
        case '\"':
            return QUOTE;
        case '\'':
            return APOSTROPHE;
        case '(':
            return LPAREN;
        case ')':
            return RPAREN;
        case '[':
            return LSQUARE;
        case ']':
            return RSQUARE;
        case '{':
            return LCURLY;
        case '}':
            return RCURLY;
        case '.':
            return DOT;
        case ',':
            return COMMA;
        case ':':
            return COLON;
        case ';':
            return SEMICOLON;
        case '?':
            return QUESTION;
        case '#':
            return POUND;
        case '_':
            return UNDERSCORE;
        case '~':
            return NEGATE;
        case '`':
            return BACKTICK;
        // case '√':
        //     return SQRT;
        // case '∛':
        //     return CBRT;
        case ' ':
            return WHITESPACE;
        case '\n':
            return WHITESPACE;
        case '\r':
            return WHITESPACE;
        case '\t':
            return WHITESPACE;
        default:
            return NONE;
    }
}
std::string getTypeString(Type type) {
    switch (type) {
        case NUM:
            return "NUM";
        case DOT:
            return "DOT";
        case COMMA:
            return "COMMA";
        case SEMICOLON:
            return "SEMICOLON";
        case COLON:
            return "COLON";
        case EQUALS:
            return "EQUALS";
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case STAR:
            return "STAR";
        case AMP:
            return "AMP";
        case PCT:
            return "PCT";
        case CARET:
            return "CARET";
        case SLASH:
            return "SLASH";
        case BACKSLASH:
            return "BACKSLASH";
        case PIPE:
            return "PIPE";
        case STR:
            return "STR";
        case QUOTE:
            return "QUOTE";
        case APOSTROPHE:
            return "APOSTROPHE";
        case LPAREN:
            return "LPAREN";
        case RPAREN:
            return "RPAREN";
        case LSQUARE:
            return "LSQUARE";
        case RSQUARE:
            return "RSQUARE";
        case LCURLY:
            return "LCURLY";
        case RCURLY:
            return "RCURLY";
        case UNDERSCORE:
            return "UNDERSCORE";
        case WHITESPACE:
            return "WHITESPACE";
        default:
            return "NONE";
    }
}

void scan(const std::string& str, std::list<Token>& tokens) {
    istringstream iss{str};
    scan(iss, tokens);
}
void scan(std::istream& in, std::list<Token>& tokens) {
    char c;
    ostringstream token;
    Type current = NONE;
    while (in.get(c)) {
        Type type = getType(c);
        // cout << token.str() << " " << getTypeString(current) << "    " << c << " " << getTypeString(type) << endl;
        if (current == NONE) {
            current = type;
        } else if (current == type) {
            if (type == EQUALS) {
                current = EQUALS_EQUALS;
            } else if (type == PLUS) {
                current = PLUS_PLUS;
            } else if (type == MINUS) {
                current = MINUS_MINUS;
            } else if (type == STAR) {
                current = STAR_STAR;
            } else if (type == SLASH) {
                current = SLASH_SLASH;
            } else if (type == AMP) {
                current = AMP_AMP;
            } else if (type == PIPE) {
                current = PIPE_PIPE;
            }
        } else if ((current == STR && (type == NUM || type == UNDERSCORE)) ||
                   (current == UNDERSCORE && (type == STR || type == NUM))) {
            current = STR;
        } else if ((current == NUM && type == DOT) || 
                   (current == NUM && type == STR && (c == 'e' || c == 'E'))) {
            current = NUM;
        } else if (current == PLUS && type == EQUALS) {
            current = PLUS_EQUALS;
        } else if (current == MINUS && type == EQUALS) {
            current = MINUS_EQUALS;
        } else if (current == STAR && type == EQUALS) {
            current = STAR_EQUALS;
        } else if (current == SLASH && type == EQUALS) {
            current = SLASH_EQUALS;
        } else if (current == MOD && type == EQUALS) {
            current = MOD_EQUALS;
        } else if (current == CARET && type == EQUALS) {
            current = CARET_EQUALS;
        } else if (current == MINUS && type == GREATER_THAN) {
            current = R_ARROW;
        } else if (current == LESS_THAN && type == MINUS) {
            current = L_ARROW;
        } else {
            if (!token.str().empty()) {
                tokens.emplace_back(Token{token.str(), current});
                token = ostringstream();
            }
            current = type;
        }
        token << c;
    }
    if (!token.str().empty()) {
        tokens.emplace_back(Token{token.str(), current});
    }
}
