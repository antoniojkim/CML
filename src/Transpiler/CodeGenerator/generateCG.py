import yaml

with open("../LanguageSpecification.yml", "r") as file:
    specs = yaml.load(file)

productions = {}
for rule in specs["productionRules"]:
    rule = rule.split(" ")
    if len(rule) > 1:
        if rule[0] not in productions:
            productions[rule[0]] = []
        
        productions[rule[0]].append(rule[1:])

#########################################
############ codeGenerator.h ############
#########################################

with open("./codeGenerator.h", "w") as out:
    out.write("""
#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <iostream>
#include <string>
#include "../ContextSensitiveTrees/ContextSensitiveTrees.h"
#include "../Parser/parsetree.h"

typedef std::ostream& (*GenerateFunction)(ContextSensitiveTree* tree, std::ostream& out, const std::string& indent);
typedef GenerateFunction (*GetGenerateFunction)(ParseTree* tree);

GenerateFunction getCodeGenerationFunction(ParseTree* tree);
    \n""")
    for root in productions:
        out.write(f"GenerateFunction get_{root}_code_generation_function(ParseTree* tree);\n")
    out.write("""

#endif // CODE_GENERATOR_H
    \n""")



#########################################
############ codeGenerator.cc ############
#########################################

with open("./codeGenerator.cc", "w") as out:
    out.write("""
#include "./codeGenerator.h"
#include <map>

using namespace std;
    \n""")
    out.write("\nmap<string, GetGenerateFunction> generateFunctionsMap = {\n")
    out.write("    "+",\n    ".join(
        f"{{\"{root}\", get_{root}_code_generation_function}}"
        for root in productions
    ))
    out.write("};\n")
    out.write("""
GenerateFunction getCodeGenerationFunction(ParseTree* tree){
    return generateFunctionsMap[tree->getRoot()](tree);
}
    """)
    


############################################
############ otherGenerators.cc ############
############################################

for root in productions:

    existingImplementations = {}
    try:
        with open(f"./Generators/{root}Generator.cc") as file:
            for row in file:
                if row.startswith("ostream& generate_"):
                    fname = row.strip().split(" ")[1].split("(")[0]
                    paren_count = 0
                    brace_count = 0
                    implementation = ""
                    while True:
                        for c in list(row):
                            if (brace_count > 0):
                                implementation += c
                            if c == "{":
                                brace_count += 1
                            elif c == "}":
                                brace_count -= 1
                            elif c == "(":
                                paren_count += 1
                            elif c == ")":
                                paren_count -= 1
                        if (paren_count > 0 or brace_count > 0):
                            row = next(file)
                        else:
                            break

                    existingImplementations[fname] = implementation
    except:
        pass


    with open(f"./Generators/{root}Generator.cc", "w") as out:
        out.write("""
#include "../codeGenerator.h"
#include <cassert>

using namespace std;
\n""")

        for rules in productions[root]:
            fname = f"generate_{root}_{'_'.join(rules)}"
            out.write(f"ostream& {fname}(ContextSensitiveTree* tree, ostream& out, const string& indent){{")
            if fname in existingImplementations:
                out.write(existingImplementations[fname])
            else:
                out.write(f'\n    assert(tree->getParams()->rule == "{root} {" ".join(rules)}");\n')
                out.write(f'    throw "{fname} not implemented";\n}}')

            out.write("\n")

        out.write(f"\nmap<string, GenerateFunction> generate_{root}_map = {{\n")
        out.write("    "+",\n    ".join(
            f"{{\"{root} {' '.join(rules)}\", generate_{root}_{'_'.join(rules)}}}"
            for rules in productions[root]
        ))
        out.write("};\n")
        out.write(f"""
GenerateFunction get_{root}_code_generation_function(ParseTree* tree){{
    NonTerminal* nt = tree->getNonTerminal();
    return generate_{root}_map[nt->getRule()];
}}
        """)
