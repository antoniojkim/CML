#ifndef CONTEXT_SENSITIVE_TREES_H
#define CONTEXT_SENSITIVE_TREES_H

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include "../CodeGenerator/codeGenerator.h"
#include "../Parser/parsetree.h"

std::string extractLexeme(ParseTree* tree);
bool isTypeNumeric(const std::string& type);

class ContextSensitiveTree;

struct Params {
    std::string rule;
    ContextSensitiveTree* parent;
};

typedef void (*InitFunction)(ParseTree* tree, ContextSensitiveTree* parent);
typedef std::ostream& (*GenerateFunction)(ContextSensitiveTree* tree, std::ostream& out, const std::string& indent);
typedef void (*TypeCheckFunction)(std::unique_ptr<Params>& p);

class ContextSensitiveTree {
   protected:
    std::string type;
    std::unique_ptr<Params> p;

    TypeCheckFunction checkType;
    GenerateFunction generateTree;
    GenerateFunction generateCode;

   public:
    ContextSensitiveTree(InitFunction init, ParseTree* tree, ContextSensitiveTree* parent = nullptr,
                         GenerateFunction generateTree = nullptr, GenerateFunction generateCode = nullptr,
                         TypeCheckFunction checkType = nullptr);

    std::string& getType();
    void setType(const std::string& type);
    bool compareType(const std::string& type);
    std::unique_ptr<Params>& getParams();
};

typedef std::unique_ptr<ContextSensitiveTree> CST;
typedef CST (*ContextGenerationfunction)(ParseTree*, ContextSensitiveTree*);  // function pointer type
extern std::map<std::string, ContextGenerationfunction> generationMap;

template <class C>
CST generateC(ParseTree*, ContextSensitiveTree*);

CST generateContextSensitiveTree(ParseTree* tree);
CST generateGlobals(ParseTree* tree, ContextSensitiveTree* parent);
CST generateProcedure(ParseTree* tree, ContextSensitiveTree* parent);
CST generateDcl(ParseTree* tree, ContextSensitiveTree* parent);
CST generateStatement(ParseTree* tree, ContextSensitiveTree* parent);
CST generateBoolean(ParseTree* tree, ContextSensitiveTree* parent);
CST generateExpr(ParseTree* tree, ContextSensitiveTree* parent);
CST generateTerm(ParseTree* tree, ContextSensitiveTree* parent);

#endif  // CONTEXT_SENSITIVE_TREES_H
