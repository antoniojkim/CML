
import yaml

with open("../LanguageSpecification.yml", "r") as file:
    specs = yaml.load(file)

###################################
############ scanner.h ############
###################################

with open("scanner.h", "w") as header:
    header.write("""
#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <map>
    \n""")

    header.write("enum Type {\n\t")
    header.write(",\n\t".join([
            f"{key}" for token in specs["tokens"] for key in token
        ]+[
            f"{key}" for keyword in specs["keywords"] for key in keyword
    ]))
    header.write(f",\n\tWHITESPACE")
    header.write(f",\n\tNONE")
    header.write("\n};\n")
    # header.write("extern std::map<std::string, Type> keywordType;\n")
    # header.write("extern std::map<Type, std::string> keywordLexeme;\n")
    # header.write("extern std::map<std::string, Type> tokenType;\n")
    # header.write("extern std::map<Type, std::string> typeLexeme;\n")
    # header.write("extern std::map<char, Type> charType;\n")

    header.write("""
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
    """)


with open("scanner.cc", "w") as source:

    source.write("""
#include "scanner.h"
#include <sstream>

using namespace std;
    \n""")

    keywordType = {keyword[key]['lexeme']: key for keyword in specs["keywords"] for key in keyword}
    source.write("map<string, Type> keywordType = {\n\t")
    source.write(",\n\t".join([f"{{\"{k}\", {v}}}" for k, v in keywordType.items()]))
    source.write("\n};\n")

    keywordLexeme = {v:k for k, v in keywordType.items()}
    source.write("map<Type, string> keywordLexeme = {\n\t")
    source.write(",\n\t".join([f"{{{k}, \"{v.upper()}\"}}" for k, v in keywordLexeme.items()]))
    source.write("\n};\n")

    tokenType = {token[key]['lexeme'].replace("\"", "\\\""):key for token in specs["tokens"] for key in token if "lexeme" in token[key]}    
    source.write("map<string, Type> tokenType = {\n\t")
    source.write(",\n\t".join([f"{{\"{k}\", {v}}}" for k, v in tokenType.items()]))
    source.write("\n};\n")

    typeLexeme = {v:k for k, v in tokenType.items()}
    source.write("map<Type, string> typeLexeme = {\n\t")
    source.write(",\n\t".join([f"{{{k}, \"{k}\"}}" for k, v in typeLexeme.items()]))
    source.write("\n};\n")

    charType = {k.replace("'", "\\'"):v for k, v in tokenType.items() if len(k) == 1 or k == "\\\""}
    source.write("map<char, Type> charType = {\n\t")
    source.write(",\n\t".join([f"{{'{k}', {v}}}" for k, v in charType.items()]))
    source.write("\n};\n")

    source.write("""
Type getType(char c) {
    if ('0' <= c && c <= '9')  return NUM;
    if ('a' <= c && c <= 'z')  return ID;
    if ('A' <= c && c <= 'Z')  return ID;
    if (charType.count(c) > 0) return charType[c];

    switch(c){
        case ' ':
            return WHITESPACE;
        case '\\t':
            return WHITESPACE;
        case '\\n':
            return WHITESPACE;
        case '\\r':
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
    """)

    source.write("""
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
    """)

    source.write("\n")
    for k, v in tokenType.items():
        if len(k) == 2 and k[0] in tokenType and k[1] in tokenType: 
            source.write(f"        }} else if (current == {tokenType[k[0]]} && type == {tokenType[k[1]]}) {{ /*  {k}  */\n")
            source.write(f"            current = {tokenType[k]};\n")

    source.write("""
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
    """)