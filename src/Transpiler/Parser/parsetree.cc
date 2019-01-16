
#include "parsetree.h"
#include <sstream>
#include "../Scanner/scanner.h"

using namespace std;

Terminal::Terminal(const Token& token)
    : token{token}, typeString{getTypeString(token.type)} {}
bool Terminal::isTerminal() { return true; }
std::string& Terminal::getRoot() { return typeString; }

Token& Terminal::getToken() { return token; }

std::ostream& Terminal::print(std::ostream& out, const std::string& indent) {
    out << indent << getTypeString(token.type) << " " << token.lexeme << endl;
    return out;
}

NonTerminal::NonTerminal(const list<string>& rule) {
    bool rootSet = false;
    bool first = true;
    ostringstream oss;
    for (auto& s : rule) {
        if (!rootSet) {
            root = s;
            rootSet = true;
        } else {
            if (first) {
                first = false;
            } else {
                oss << " ";
            }
            oss << s;
        }
    }
    this->rule = oss.str();
}

void NonTerminal::reserve(const int& num) {
    children.clear();
    children.reserve(num);
}

void NonTerminal::addChild(unique_ptr<ParseTree>& child) {
    children.emplace_back(std::move(child));
}

vector<unique_ptr<ParseTree>>& NonTerminal::getChildren() { return children; }
std::unique_ptr<ParseTree>& NonTerminal::getChild(const int& i) { return children[i]; }

string& NonTerminal::getRoot() { return root; }
bool NonTerminal::isTerminal() { return false; }

std::ostream& NonTerminal::print(std::ostream& out, const std::string& indent) {
    out << indent << root << " " << rule << endl;
    for (auto& child : children) {
        // if (!child->isTerminal()){
        child->print(out, indent + "    ");
        // }
    }
    return out;
}
