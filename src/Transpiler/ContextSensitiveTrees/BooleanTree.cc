
#include "ContextSensitiveTrees.h"

using namespace std;

// std::map<std::string, std::map<std::string, std::map<std::string, bool>>>
//     supportedBooleanOperators =  // map<left, map<comparator, map<right,
//     bool>>>
//     {{"string", {"==", {"string", true}}}};

class NegBoolean : public ContextSensitiveTree {
    unique_ptr<ContextSensitiveTree> expr;

   public:
    NegBoolean(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        NonTerminal* boolean = tree->getNonTerminal();
        expr = generateExpr(boolean->getChild(1).get(), this);
        setType("bool");
    }

    void checkContext() override {
        expr->checkContext();
        if (expr->getType() != "bool")
            throw "Expr not type bool: " + expr->getType();
    }

    ostream& generateTree(ostream& out, const string& indent) override {
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        out << indent;
        left->generateCode(out, "");
        if (!comparator.empty()) {
            out << " " << comparator << " ";
            right->generateCode(out, "");
        }
        return out;
    }
};
class BooleanExpr : public ContextSensitiveTree {
    unique_ptr<ContextSensitiveTree> left;
    unique_ptr<ContextSensitiveTree> right;
    string comparator;

   public:
    BooleanExpr(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        NonTerminal* boolean = tree->getNonTerminal();
        left = generateExpr(boolean->getChild(0).get(), this);
        if (boolean->getChildren().size() >= 3) {
            comparator = extractLexeme(boolean->getChild(1).get());
            right = generateExpr(boolean->getChild(2).get(), this);
            setType("bool");
        } else {
            setType(left->getType());
        }
    }

    void checkContext() override {
        if (comparator.empty()) {
            left->checkContext();
        } else {
            right->checkContext();
            // if (left->getType() != right->getType() &&
            //     !isTypeNumeric(left->getType()) &&
            //     !isTypeNumeric(right->getType())) {
            //     throw "Left type does not match right type:  " +
            //         left->getType() + " " + comparator + " " +
            //         right->getType();
            // }
            // if (!(isTypeNumeric(left->getType()) &&
            //       isTypeNumeric(right->getType())) &&
            //     supportedBooleanOperators.count(left->getType()) > 0 &&
            //     (supportedBooleanOperators.at(left->getType()).count(comparator)
            //     ==
            //          0 ||
            //      supportedBooleanOperators.at(left->getType())
            //              .at(comparator)
            //              .count(right->getType()) == 0)) {
            //     throw "Unsupported operator:  " + left->getType() + " " +
            //         comparator + " " + right->getType();
            // }
        }
    }

    ostream& generateTree(ostream& out, const string& indent) override {
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        out << indent;
        left->generateCode(out, "");
        if (!comparator.empty()) {
            out << " " << comparator << " ";
            right->generateCode(out, "");
        }
        return out;
    }
};
class CompoundBoolean : public ContextSensitiveTree {
    unique_ptr<ContextSensitiveTree> left;
    unique_ptr<ContextSensitiveTree> right;
    string compound;

   public:
    CompoundBoolean(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        NonTerminal* boolean = tree->getNonTerminal();
        left = generateBoolean(boolean->getChild(0).get(), this);
        if (boolean->getChildren().size() >= 3) {
            compound = extractLexeme(boolean->getChild(1).get());
            right = generateBoolean(boolean->getChild(2).get(), this);
        }
    }

    void checkContext() override {
        left->checkContext();
        if (!isTypeNumeric(left->getType()))
            throw "Invalid boolean type:  " + left->getType();

        if (!compound.empty()) {
            right->checkContext();
            if (!isTypeNumeric(right->getType()))
                throw "Invalid boolean type:  " + right->getType();
        }
    }

    ostream& generateTree(ostream& out, const string& indent) override {
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        out << indent;
        left->generateCode(out, "");
        if (!compound.empty()) {
            out << " " << compound << " ";
            right->generateCode(out, "");
        }
        return out;
    }
};

std::map<std::string, ContextGenerationfunction> booleanMap = {};

unique_ptr<ContextSensitiveTree> generateBoolean(ParseTree* tree,
                                                 ContextSensitiveTree* parent) {
    return booleanMap.at(tree->getFirst())(tree, parent);
}