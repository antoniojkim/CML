
#include "ContextSensitiveTrees.h"

using namespace std;

class Procedure;

class Global : public ContextSensitiveTree {
    list<string> include;
    list<unique_ptr<ContextSensitiveTree>> children;

   public:
    Global(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        NonTerminal* globals = dynamic_cast<NonTerminal*>(tree);
        if (!globals || globals->getRoot() != "globals")
            throw "Invalid ParseTree given for Global";

        while (!globals->getChildren().empty()) {
            auto& globalRoot = globals->getChildren()[0]->getRoot();
            if (globalRoot == "include") {
                this->include.emplace_back(
                    extractLexeme(globals->getChildren()[0].get()));
            } else {
                this->children.emplace_back(generationMap.at(globalRoot)(
                    globals->getChildren()[1].get(), this));
            }
            globals =
                dynamic_cast<NonTerminal*>(globals->getChildren()[1].get());
        }
    }

    void checkContext() override {
        for (auto& child : children) {
            child->checkContext();
        }
    }

    ostream& generateTree(ostream& out, const string& indent) override {
        out << indent << "Global:" << endl;
        out << indent << "    Include:" << endl;
        for (auto& s : include) {
            out << indent << "        " << s << endl;
        }
        for (auto& child : children) {
            child->generateTree(out, indent + "    ");
        }
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        out << endl;
        for (auto& s : include) {
            out << indent << "#include <" << s << ">" << endl;
        }
        out << endl << endl;
        for (auto& child : children) {
            child->generateCode(out, indent);
        }
        return out;
    }
};

unique_ptr<ContextSensitiveTree> generateGlobals(ParseTree* tree,
                                                 ContextSensitiveTree* parent) {
    return make_unique<Global>(tree, parent);
}
