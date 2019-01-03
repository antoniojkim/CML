
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
    header.write("extern std::map<std::string, Type> keywords;\n")
    header.write("extern std::map<std::string, Type> charType;\n")

    header.write("""
Type getType(char c);
std::string getTypeString(Type type);

struct Token {
    std::string lexeme;
    Type type;
};

void scan(const std::string& str, std::list<Token>& tokens);
void scan(std::istream& in, std::list<Token>& tokens);

#endif
    """)


with open("scanner.cc", "w") as source:

    source.write("""
#include "scanner.h"
#include <sstream>

using namespace std;
    \n""")

    source.write("map<string, Type> keywords = {\n\t")
    source.write(",\n\t".join([
        f"{{\"{keyword[key]['lexeme']}\", {key}}}" for keyword in specs["keywords"] for key in keyword
    ]))
    source.write("\n};\n")
    source.write("map<string, Type> charType = {\n\t")
    source.write(",\n\t".join([
        f"{{\"{token[key]['lexeme']}\", {key}}}" for token in specs["tokens"] for key in token if "lexeme" in token[key]
    ]))
    source.write("\n};\n")