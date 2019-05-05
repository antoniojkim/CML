
#include "ContextSensitiveTrees.h"

using namespace std;

class AddExpr : public ContextSensitiveTree {
    unique_ptr<ContextSensitiveTree> expr;
    unique_ptr<ContextSensitiveTree> term;

   public:
    AddExpr(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        NonTerminal* expr = tree->getNonTerminal();
        this->expr = generateExpr(expr->getChild(0).get(), this);
        this->term = generateTerm(expr->getChild(2).get(), this);
    }

    void checkContext() override {}

    ostream& generateTree(ostream& out, const string& indent) override {
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        out << indent;
        expr->generateCode(out, "");
        out << " + ";
        term->generateCode(out, "");
        return out;
    }
};
class SubExpr : public ContextSensitiveTree {
    unique_ptr<ContextSensitiveTree> expr;
    unique_ptr<ContextSensitiveTree> term;

   public:
    SubExpr(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        NonTerminal* expr = tree->getNonTerminal();
        this->expr = generateExpr(expr->getChild(0).get(), this);
        this->term = generateTerm(expr->getChild(2).get(), this);
    }

    void checkContext() override {}

    ostream& generateTree(ostream& out, const string& indent) override {
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        out << indent;
        expr->generateCode(out, "");
        out << " + ";
        term->generateCode(out, "");
        return out;
    }
};

std::map<std::string, ContextGenerationfunction> statementMap = {
    {"term", generateTerm}};

unique_ptr<ContextSensitiveTree> generateExpr(ParseTree* tree,
                                              ContextSensitiveTree* parent) {
    NonTerminal* expr = tree->getNonTerminal();
    if (expr->getFirst() == "term") {
        return generateTerm(expr->getChild(1).get(), parent);
    }
    string op = expr->getChild(1)->getTerminal()->getToken().lexeme;
    if (op == "+") {
        return make_unique<AddExpr>(tree, parent);
    } else if (op == "-") {
        return make_unique<SubExpr>(tree, parent);
    }
    throw "Unimplemented operator:  " + op;
}
