#ifndef PARSETREE_H
#define PARSETREE_H

#include <string>
#include <memory>
#include <vector>
#include "../Scanner/scanner.h"


struct ParseTree {
    virtual std::string& getRoot() = 0;
    virtual bool isTerminal() = 0;
};

class Terminal : public ParseTree {
    Token token;
    std::string typeString;

    public:
        Terminal(const Token& token);

        std::string& getRoot() override;
        bool isTerminal() override;
};

class NonTerminal : public ParseTree {
    std::string root;
    std::string rule;
    std::vector<std::unique_ptr<ParseTree>> children;

    public:
        NonTerminal(const std::list<std::string>& rule);

        void reserve(const int& num);
        void addChild(std::unique_ptr<ParseTree>& child);
        std::vector<std::unique_ptr<ParseTree>>& getChildren();

        std::string& getRoot() override;
        bool isTerminal() override;
};


#endif // PARSETREE_H

