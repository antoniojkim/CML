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
############ semanticAnalyser.h ############
#########################################

with open("./semanticAnalyser.h", "w") as out:
    out.write("""
#ifndef SEMANTIC_ANALYSIS_H
#define SEMANTIC_ANALYSIS_H

#include <iostream>
#include <string>
#include "../ContextSensitiveTrees/ContextSensitiveTrees.h"
#include "../Parser/parsetree.h"

typedef std::ostream& (*AnalysisFunction)(ContextSensitiveTree* tree, std::ostream& out, const std::string& indent);
typedef AnalysisFunction (*GetAnalysisFunction)(ParseTree* tree);

AnalysisFunction getSemanticAnalysisFunction(ParseTree* tree);
    \n""")
    for root in productions:
        out.write(f"AnalysisFunction get_{root}_semantic_analysis_function(ParseTree* tree);\n")
    out.write("""

#endif // SEMANTIC_ANALYSIS_H
    \n""")



#########################################
############ semanticAnalyser.cc ############
#########################################

with open("./semanticAnalyser.cc", "w") as out:
    out.write("""
#include "./semanticAnalyser.h"
#include <map>

using namespace std;
    \n""")
    out.write("\nmap<string, GetAnalysisFunction> analysisFunctionsMap = {\n")
    out.write("    "+",\n    ".join(
        f"{{\"{root}\", get_{root}_semantic_analysis_function}}"
        for root in productions
    ))
    out.write("};\n")
    out.write("""
GenerateFunction getSemanticAnalysisFunction(ParseTree* tree){
    return analysisFunctionsMap[tree->getRoot()](tree);
}
    """)
    


############################################
############ otherSemanticAnalysis.cc ############
############################################

for root in productions:

    existingImplementations = {}
    try:
        with open(f"./Analysers/{root}Analyser.cc") as file:
            for row in file:
                if row.startswith("ostream& analyse_"):
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


    with open(f"./Analysers/{root}Analyser.cc", "w") as out:
        out.write("""
#include "../semanticAnalyser.h"
#include <cassert>

using namespace std;
\n""")

        for rules in productions[root]:
            fname = f"analyse_{root}_{'_'.join(rules)}"
            out.write(f"ostream& {fname}(ContextSensitiveTree* tree, ostream& out, const string& indent){{")
            if fname in existingImplementations:
                out.write(existingImplementations[fname])
            else:
                out.write(f'\n    assert(tree->getParams()->rule == "{root} {" ".join(rules)}");\n')
                out.write(f'    throw "{fname} not implemented";\n}}')

            out.write("\n")

        out.write(f"\nmap<string, AnalysisFunction> analyse_{root}_map = {{\n")
        out.write("    "+",\n    ".join(
            f"{{\"{root} {' '.join(rules)}\", analyse_{root}_{'_'.join(rules)}}}"
            for rules in productions[root]
        ))
        out.write("};\n")
        out.write(f"""
AnalysisFunction get_{root}_semantic_analysis_function(ParseTree* tree){{
    NonTerminal* nt = tree->getNonTerminal();
    return analyse_{root}_map[nt->getRule()];
}}
        """)
