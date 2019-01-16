
#include "ContextSensitiveTrees.h"
#include <map>
#include <sstream>

using namespace std;

string extractLexeme(ParseTree* tree) {
    if (tree->isTerminal()) {
        Terminal* t = dynamic_cast<Terminal*>(tree);
        return t->getToken().lexeme;
    }

    NonTerminal* nt = dynamic_cast<NonTerminal*>(tree);
    ostringstream lexeme;
    bool first = true;
    for (auto& child : nt->getChildren()) {
        if (first) {
            first = false;
        } else {
            lexeme << " ";
        }
        lexeme << extractLexeme(child.get());
    }
    return lexeme.str();
}

ContextSensitiveTree::ContextSensitiveTree(ContextSensitiveTree* parent)
    : parent{parent} {}

std::string& ContextSensitiveTree::getType() { return type; }
void ContextSensitiveTree::setType(const std::string& type) {
    if (this->type.empty()) {
        this->type = type;
    }
}
bool ContextSensitiveTree::compareType(const std::string& type) {
    if (this->type.empty()) {
        this->type = type;
        return true;
    }
    return this->type == type;
}

/* Template:

class  : public ContextSensitiveTree {
   public:
    (ParseTree* tree, ContextSensitiveTree* parent): ContextSensitiveTree{parent} {

    }

    void checkContext() override {}

    std::ostream& generateTree(std::ostream& out,
                               const std::string& indent) override { return out; }
    std::ostream& generateCode(std::ostream& out,
                               const std::string& indent) override { return out; }

};

*/


std::map<std::string, ContextGenerationfunction> generationMap = {
    {"globals", generateGlobals},
    {"procedure", generateProcedure},
    {"dcl", generateDcl},
    {"expr", generateExpr},
    {"statement", generateStatement}
};

std::unique_ptr<ContextSensitiveTree> generateContextSensitiveTree(
    ParseTree* tree) {
    return generationMap[tree->getRoot()](tree, nullptr);
}