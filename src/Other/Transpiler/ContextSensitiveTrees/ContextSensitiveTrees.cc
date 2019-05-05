
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
map<string, bool> numericTypes = {
    {"int", true}, {"long", true}, {"long", true}, {"float", true}, {"double", true}, {"bool", true}, {"char", true}};
bool isTypeNumeric(const std::string& type) {
    istringstream iss{type};
    string s;
    while (iss >> s) {
        if (numericTypes.count(s) == 0 && s != "unsigned") {
            return false;
        }
    }
    return true;
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
    std::unique_ptr<Params>& ContextSensitiveTree::getParams(){ return p; }

/* Template:

#include "ContextSensitiveTrees.h"

using namespace std;

class  : public ContextSensitiveTree {
   public:
    (ParseTree* tree, ContextSensitiveTree* parent):
ContextSensitiveTree{parent} {

    }

    void checkContext() override {}

    ostream& generateTree(ostream& out, const string& indent) override { return
out; } ostream& generateCode(ostream& out, const string& indent) override {
return out; }

};

*/

template <class C>
CST generateC(ParseTree* tree, ContextSensitiveTree* parent) {
    return make_unique<C>(tree, parent);
}

std::map<std::string, ContextGenerationfunction> generationMap = {
    {"globals", generateGlobals},
    {"procedure", generateProcedure},
    {"dcl", generateDcl},
    {"expr", generateExpr},
    {"statement", generateStatement},
    {"statements", generateStatement},
    {"boolean", generateBoolean}};

std::unique_ptr<ContextSensitiveTree> generateContextSensitiveTree(
    ParseTree* tree) {
    return generationMap[tree->getRoot()](tree, nullptr);
}