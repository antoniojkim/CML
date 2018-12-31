import yaml

with open("../LanguageSpecification.yml", "r") as file:
    specs = yaml.load(file)


terminals = ["BOF", "EOF"]
for token in specs["tokens"]:
    terminals.extend([key for key in token])
for keyword in specs["keywords"]:
    terminals.extend([key for key in keyword])

nonterminals = []
for nonterminal in specs["nonterminalSymbols"]:
    nonterminals.append(nonterminal)

productionRules = []
for rule in specs["productionRules"]:
    productionRules.append(rule.split(" "))

transitions = []
productions = {}
for rule in productionRules:
    if rule[0] in productions:
        productions[rule[0]].append(rule[1:])
    else:
        productions[rule[0]] = [rule[1:]]

states = []


terminals.sort()
nonterminals.sort()

with open("./CML.lr1", "w") as file:
    file.write(f"{len(terminals)}\n")
    file.write("\n".join(terminals)+"\n")
    file.write(f"{len(nonterminals)}\n")
    file.write("\n".join(nonterminals)+"\n")
    file.write(f"{len(productionRules)}\n")
    file.write("\n".join([" ".join(rule) for rule in productionRules])+"\n")
    file.write(f"{len(states)}\n")
    file.write(f"{len(transitions)}\n")
    file.write("\n".join(transitions)+"\n")