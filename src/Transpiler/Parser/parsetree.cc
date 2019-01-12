
#include "../Scanner/scanner.h"
#include "parsetree.h"
#include <sstream>

using namespace std;

Terminal::Terminal(const Token& token) : token{token}, typeString{getTypeString(token.type)} {}
bool Terminal::isTerminal() { return true; }
std::string& Terminal::getRoot() { return typeString; }


NonTerminal::NonTerminal(const list<string>& rule) {
    bool rootSet = false;
    bool first = false;
    ostringstream oss;
    for (auto& s : rule) {
        if (!rootSet) {
            root = s;
            rootSet = true;
        } else {
            if (!first) {
                oss << " ";
            } else {
                first = true;
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

string& NonTerminal::getRoot() { return root; }
bool NonTerminal::isTerminal() { return false; }
