#ifndef CONTEXT_SENSITIVE_TREES_H
#define CONTEXT_SENSITIVE_TREES_H

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include "../Parser/parsetree.h"

std::string extractLexeme(ParseTree* tree);

class ContextSensitiveTree {
   protected:
    std::string type;
    ContextSensitiveTree* parent;

   public:
    ContextSensitiveTree(ContextSensitiveTree* parent = nullptr);

    std::string& getType();
    void setType(const std::string& type);
    bool compareType(const std::string& type);
    virtual void checkContext() = 0;

    virtual std::ostream& generateTree(std::ostream& out,
                                       const std::string& indent = "") = 0;
    virtual std::ostream& generateCode(std::ostream& out,
                                       const std::string& indent = "") = 0;
};

typedef std::unique_ptr<ContextSensitiveTree> CST;
typedef CST (*ContextGenerationfunction)(
    ParseTree*, ContextSensitiveTree*);  // function pointer type
extern std::map<std::string, ContextGenerationfunction> generationMap;

template<class C>
CST generateC(ParseTree*, ContextSensitiveTree*);

CST generateContextSensitiveTree(ParseTree* tree);
CST generateGlobals(ParseTree* tree, ContextSensitiveTree* parent);
CST generateProcedure(ParseTree* tree, ContextSensitiveTree* parent);
CST generateDcl(ParseTree* tree, ContextSensitiveTree* parent);
CST generateExpr(ParseTree* tree, ContextSensitiveTree* parent);
CST generateStatement(ParseTree* tree, ContextSensitiveTree* parent);

#endif  // CONTEXT_SENSITIVE_TREES_H
