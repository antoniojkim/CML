
#include "ContextSensitiveTrees.h"

using namespace std;

class Statement : public ContextSensitiveTree {
   public:
    Statement(ParseTree* tree, ContextSensitiveTree* parent): ContextSensitiveTree{parent} {

    }

    void checkContext() override {}

    std::ostream& generateTree(std::ostream& out,
                               const std::string& indent) override { return out; }
    std::ostream& generateCode(std::ostream& out,
                               const std::string& indent) override { return out; }

};


unique_ptr<ContextSensitiveTree> generateStatement(ParseTree* tree, ContextSensitiveTree* parent) {
    return make_unique<Statement>(tree, parent);
}
