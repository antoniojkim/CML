
#include "ContextSensitiveTrees.h"

using namespace std;

class Expr : public ContextSensitiveTree {
   public:
    Expr(ParseTree* tree, ContextSensitiveTree* parent)
        : ContextSensitiveTree{parent} {}

    void checkContext() override {}

    ostream& generateTree(ostream& out, const string& indent) override {
        return out;
    }
    ostream& generateCode(ostream& out, const string& indent) override {
        return out;
    }
};

unique_ptr<ContextSensitiveTree> generateExpr(ParseTree* tree,
                                              ContextSensitiveTree* parent) {
    return make_unique<Expr>(tree, parent);
}
