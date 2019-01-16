
#include "ContextSensitiveTrees.h"

using namespace std;

class Procedure : public ContextSensitiveTree {
    std::string name;
    std::list<std::unique_ptr<ContextSensitiveTree>> params;
    std::list<std::unique_ptr<ContextSensitiveTree>> statements;

   public:
    Procedure(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        NonTerminal* procedure = dynamic_cast<NonTerminal*>(tree);
        if (!procedure || procedure->getRoot() != "procedure")
            throw "Invalid ParseTree given for Procedure";

        type = extractLexeme(procedure->getChild(0).get());  // return type
        name = extractLexeme(procedure->getChild(1).get());

        NonTerminal* params =
            dynamic_cast<NonTerminal*>(procedure->getChild(3).get());
        while (!params->getChildren().empty()) {
            this->params.emplace_back(
                generationMap["dcl"](params->getChild(0).get(), this));
            params = dynamic_cast<NonTerminal*>(params->getChildren()[1].get());
        }

        NonTerminal* statements =
            dynamic_cast<NonTerminal*>(procedure->getChild(6).get());
        while (!statements->getChildren().empty()) {
            this->statements.emplace_back(generationMap["statement"](
                statements->getChild(1).get(), this));
            statements =
                dynamic_cast<NonTerminal*>(statements->getChildren()[0].get());
        }
    }

    void checkContext() override {
        for (auto& param : params) {
            param->checkContext();
        }
        for (auto& statement : statements) {
            statement->checkContext();
        }
    }

    ostream& generateTree(ostream& out, const string& indent) override {
        out << indent << "Name:  " << name << "    Return Type:  " << type
            << endl
            << indent << "Params:" << endl;
        for (auto& p : params) {
            p->generateTree(out, indent + "    ");
        }
        out << indent << "Statements:" << endl;
        for (auto& s : statements) {
            s->generateTree(out, indent + "    ");
        }
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        out << indent << type << " " << name << "(";
        bool first = true;
        for (auto& p : params) {
            if (first) {
                first = false;
            } else {
                out << ", ";
            }
            p->generateCode(out, "");
        }
        out << ") {" << endl;
        for (auto& s : statements) {
            s->generateCode(out, indent + "    ");
        }
        out << "}" << endl;
        return out;
    }
};

unique_ptr<ContextSensitiveTree> generateProcedure(ParseTree* tree,
                                                 ContextSensitiveTree* parent) {
    return make_unique<Procedure>(tree, parent);
}
