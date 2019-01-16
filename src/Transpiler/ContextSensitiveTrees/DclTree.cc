
#include "ContextSensitiveTrees.h"

using namespace std;

class Dcl : public ContextSensitiveTree {
   protected:
    std::string name;
    std::unique_ptr<ContextSensitiveTree> defaultValue;

   public:
    Dcl(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {
        NonTerminal* dcl = dynamic_cast<NonTerminal*>(tree);
        if (!dcl || dcl->getRoot() != "dcl")
            throw "Invalid ParseTree given for Dcl";
        
        type = extractLexeme(dcl->getChildren()[0].get());
        name = extractLexeme(dcl->getChildren()[1].get());

        if (dcl->getChildren().size() == 4){
            defaultValue = generationMap["expr"](dcl->getChildren()[3].get(), this);
        }
    }

    void checkContext() override {
        if (defaultValue != nullptr && type != defaultValue->getType()) {
            throw "Param expected type " + type + " but found " +
                defaultValue->getType();
        }
    }

    std::ostream& generateTree(std::ostream& out,
                                       const std::string& indent) override {
        return generateCode(out, indent);
    }
    std::ostream& generateCode(std::ostream& out,
                                       const std::string& indent) override {
        out << indent << type << " " << name;
        if (defaultValue != nullptr) {
            out << " = ";
            defaultValue->generateCode(out, "");
        }
        return out;
    }
};

unique_ptr<ContextSensitiveTree> generateDcl(ParseTree* tree,
                                                 ContextSensitiveTree* parent) {
    return make_unique<Dcl>(tree, parent);
}
