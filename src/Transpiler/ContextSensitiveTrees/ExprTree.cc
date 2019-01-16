
#include "ContextSensitiveTrees.h"

using namespace std;

class Expr : public ContextSensitiveTree {
   public:
    Expr(ParseTree* tree, ContextSensitiveTree* parent): ContextSensitiveTree{parent} {

    }

    void checkContext() override {}

    std::ostream& generateTree(std::ostream& out,
                               const std::string& indent) override { return out; }
    std::ostream& generateCode(std::ostream& out,
                               const std::string& indent) override { return out; }

};


unique_ptr<ContextSensitiveTree> generateExpr(ParseTree* tree, ContextSensitiveTree* parent) {
    return make_unique<Expr>(tree, parent);
}
