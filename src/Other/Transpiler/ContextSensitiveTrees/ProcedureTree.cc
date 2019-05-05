
#include "ContextSensitiveTrees.h"

using namespace std;

class Procedure : public ContextSensitiveTree {
    std::string name;
    std::list<std::unique_ptr<ContextSensitiveTree>> params;
    std::unique_ptr<ContextSensitiveTree> statements;

   public:
    Procedure(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        NonTerminal* procedure = tree->getNonTerminal();
        if (!procedure || procedure->getRoot() != "procedure")
            throw "Invalid ParseTree given for Procedure";

        type = extractLexeme(procedure->getChild(0).get());  // return type
        name = extractLexeme(procedure->getChild(1).get());

        NonTerminal* params = procedure->getChild(3)->getNonTerminal();
        while (!params->getChildren().empty()) {
            this->params.emplace_back(
                generationMap["dcl"](params->getChild(0).get(), this));
            params = params->getChild(1)->getNonTerminal();
        }

        statements =
            generationMap.at("statement")(procedure->getChild(6).get(), this);
    }

    void checkContext() override {
        for (auto& param : params) {
            param->checkContext();
        }
        // for (auto& statement : statements) {
        statements->checkContext();
        // }
    }

    ostream& generateTree(ostream& out, const string& indent) override {
        out << indent << "Name:  " << name << "    Return Type:  " << type
            << endl
            << indent << "Params:" << endl;
        for (auto& p : params) {
            p->generateTree(out, indent + "    ");
        }
        out << indent << "Statements:" << endl;
        statements->generateTree(out, indent + "    ");
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
        statements->generateCode(out, indent + "    ");
        out << "}" << endl;
        return out;
    }
};

unique_ptr<ContextSensitiveTree> generateProcedure(
    ParseTree* tree, ContextSensitiveTree* parent) {
    return make_unique<Procedure>(tree, parent);
}
