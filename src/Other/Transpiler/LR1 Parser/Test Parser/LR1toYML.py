import yaml

with open("./wlp4.lr1") as file:
    rows = [row.strip() for row in file]

current = 0
num_terminals = int(rows[current])
current += 1
terminals = [rows[i] for i in range(current, current+num_terminals)]
current += num_terminals

num_nonterminals = int(rows[current])
current += 1
nonterminals = [rows[i] for i in range(current, current+num_nonterminals)]
current += num_nonterminals

start_symbol = rows[current]
current += 1

num_productions = int(rows[current])
current += 1
productions = [rows[i] for i in range(current, current+num_productions)]
current += num_productions

num_states = int(rows[current])
current += 1
num_transitions = int(rows[current])
current += 1
transitions = [rows[i].split(" ") for i in range(current, current+num_transitions)]
transitions.sort(key=lambda x: int(x[0]))

config = {
    "tokens": [{t:{"description":""}} for t in terminals],
    "keywords": [],
    "whitespace": [],
    "nonterminalSymbols": nonterminals,
    "startSymbol": start_symbol,
    "productionRules": productions
}

with open("./wlp4.yml", "w") as file:
    yaml.dump(config, file, default_flow_style=False)

with open("./wlp4.lr1", "w") as file:
        file.write(f"{len(terminals)}\n")
        file.write("\n".join(terminals)+"\n")
        file.write(f"{len(nonterminals)}\n")
        file.write("\n".join(nonterminals)+"\n")
        file.write(f"start\n")
        file.write(f"{len(productions)}\n")
        file.write("\n".join(productions)+"\n")
        file.write(f"{num_states}\n")
        file.write(f"{len(transitions)}\n")
        file.write("\n".join(" ".join(map(str, t)) for t in transitions)+"\n")
    