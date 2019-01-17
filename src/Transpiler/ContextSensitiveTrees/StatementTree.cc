
#include "ContextSensitiveTrees.h"

using namespace std;

class ElseIfStatement;
class ElseStatement;

class IfStatement : public ContextSensitiveTree {
    unique_ptr<ContextSensitiveTree> boolean;
    unique_ptr<ContextSensitiveTree> statements;
    unique_ptr<ContextSensitiveTree> elseifStatement;
    unique_ptr<ContextSensitiveTree> elseStatement;

   public:
    IfStatement(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        NonTerminal* ifstmt = tree->getNonTerminal();
        boolean = generationMap.at("boolean")(ifstmt->getChild(2).get(), this);
        statements = generateStatement(ifstmt->getChild(5).get(), parent);
        if (!ifstmt->getChild(7)->isEmpty()) {
            elseifStatement =
                generateStatement(ifstmt->getChild(7).get(), parent);
        }
        if (!ifstmt->getChild(8)->isEmpty()) {
            elseStatement =
                generateStatement(ifstmt->getChild(8).get(), parent);
        }
    }

    void checkContext() override {
        boolean->checkContext();
        statements->checkContext();
        if (elseifStatement) elseifStatement->checkContext();
        elseStatement->checkContext();
    }

    ostream& generateTree(ostream& out, const string& indent) override {
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        out << indent << "if (";
        boolean->generateCode(out, "");
        out << ") {" << endl;
        statements->generateCode(out, indent + "    ");
        out << "}" << endl;
        if (elseifStatement) elseifStatement->generateCode(out, indent);
        if (elseStatement) elseStatement->generateCode(out, indent);
        return out;
    }
};
class ElseIfStatement : public ContextSensitiveTree {
    unique_ptr<ContextSensitiveTree> boolean;
    unique_ptr<ContextSensitiveTree> statements;
    unique_ptr<ContextSensitiveTree> elseifStatement;

   public:
    ElseIfStatement(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        NonTerminal* elseif = tree->getNonTerminal();
        boolean = generationMap.at("boolean")(elseif->getChild(3).get(), this);
        statements = generateStatement(elseif->getChild(6).get(), parent);
        if (!elseif->getChild(8)->isEmpty()) {
            elseifStatement =
                generateStatement(elseif->getChild(8).get(), parent);
        }
    }

    void checkContext() override {
        boolean->checkContext();
        statements->checkContext();
        if (elseifStatement) elseifStatement->checkContext();
    }

    ostream& generateTree(ostream& out, const string& indent) override {
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        out << indent << "else if (";
        boolean->generateCode(out, "");
        out << ") {" << endl;
        statements->generateCode(out, indent + "    ");
        out << "}" << endl;
        if (elseifStatement) elseifStatement->generateCode(out, indent);
        return out;
    }
};
class ElseStatement : public ContextSensitiveTree {
    unique_ptr<ContextSensitiveTree> statements;

   public:
    ElseStatement(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        statements =
            generateStatement(tree->getNonTerminal()->getChild(2).get(), this);
    }

    void checkContext() override { statements->checkContext(); }

    ostream& generateTree(ostream& out, const string& indent) override {
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        out << indent << "else {" << endl;
        statements->generateCode(out, indent + "    ");
        out << "}" << endl;
        return out;
    }
};
class ReturnStatement : public ContextSensitiveTree {
    unique_ptr<ContextSensitiveTree> expr;

   public:
    ReturnStatement(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        expr = generationMap.at("expr")(
            tree->getNonTerminal()->getChild(1).get(), this);
    }

    void checkContext() override {
        expr->checkContext();
        if (parent->compareType(expr->getType())) {
            throw "Return type does not match function return type";
        }
    }

    ostream& generateTree(ostream& out, const string& indent) override {
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        out << indent << "return ";
        expr->generateCode(out, "");
        out << ";";
        return out;
    }
};

class Statements : public ContextSensitiveTree {
    list<unique_ptr<ContextSensitiveTree>> statements;

   public:
    Statements(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        NonTerminal* statements = tree->getNonTerminal();
        while (!statements->getChildren().empty()) {
            this->statements.emplace_back(
                generateStatement(statements->getChild(1).get(), this));
            statements = statements->getChild(0)->getNonTerminal();
        }
    }

    void checkContext() override {
        for (auto& s : statements) {
            s->checkContext();
        }
    }

    ostream& generateTree(ostream& out, const string& indent) override {
        for (auto& s : statements) {
            s->generateTree(out, indent);
        }
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        for (auto& s : statements) {
            s->generateCode(out, indent) << endl;
        }
        return out;
    }
};

unique_ptr<ContextSensitiveTree> generateIfStatement(
    ParseTree* tree, ContextSensitiveTree* parent) {
    return make_unique<IfStatement>(tree, parent);
}
unique_ptr<ContextSensitiveTree> generateElseIfStatement(
    ParseTree* tree, ContextSensitiveTree* parent) {
    return make_unique<ElseIfStatement>(tree, parent);
}
unique_ptr<ContextSensitiveTree> generateElseStatement(
    ParseTree* tree, ContextSensitiveTree* parent) {
    return make_unique<ElseStatement>(tree, parent);
}
unique_ptr<ContextSensitiveTree> generateStatements(
    ParseTree* tree, ContextSensitiveTree* parent) {
    return make_unique<Statements>(tree, parent);
}

std::map<std::string, ContextGenerationfunction> statementMap = {
    {"dcl", generateDcl},
    {"IF", generateIfStatement},
    {"statements", generateStatements},
    {"elseifstatement", generateElseIfStatement},
    {"elsestatement", generateElseStatement}};

unique_ptr<ContextSensitiveTree> generateStatement(
    ParseTree* tree, ContextSensitiveTree* parent) {
    if (tree->getRoot() == "statement") {
        return statementMap.at(tree->getFirst())(tree, parent);
    } else {
        return statementMap.at(tree->getRoot())(tree, parent);
    }
}
