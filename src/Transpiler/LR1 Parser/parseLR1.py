
import yaml
import numpy as np

def parseLR1(infile, outfile, verbose=False):

    with open(infile, "r") as file:
        specs = yaml.load(file)
    # with open("./test.yml", "r") as file:
    #     specs = yaml.load(file)


    terminals = []
    for token in specs["tokens"]:
        terminals.extend([key for key in token])
    for keyword in specs["keywords"]:
        terminals.extend([key for key in keyword])

    if "BOF" not in terminals:
        terminals.append("BOF")
    if "EOF" not in terminals:
        terminals.append("EOF")

    start_symbol = specs["startSymbol"]

    nonterminals = []
    for nonterminal in specs["nonterminalSymbols"]:
        nonterminals.append(nonterminal)

    if start_symbol not in nonterminals:
        nonterminals.append(start_symbol)

    productionRules = []
    for rule in specs["productionRules"]:
        productionRules.append(rule.split(" "))

    productions = {}
    for i, rule in enumerate(productionRules):
        if rule[0] in productions:
            productions[rule[0]].append(i)
        else:
            productions[rule[0]] = [i]

    if "start" not in productions:
        productionRules.append(["start", "BOF_", start_symbol, "EOF_"])
        start_state = len(productionRules)-1
        productions["start"] = [start_state]
    else:
        start_state = 0

    if verbose:
        print("Rules:\n    ", end="")
        print("\n    ".join([f"{i}  "+" ".join(rule) for i, rule in enumerate(productionRules)]), "\n")


    ###############################################################################################

    nullable = {}
    first = {}
    follow = {}
    for rule in productionRules:
        nullable[rule[0]] = False
        first[rule[0]] = []
        if rule[0] != start_symbol:
            follow[rule[0]] = []

    def is_nullable(s, bool_=True):
        if s not in nullable: nullable[s] = False
        return nullable[s] == bool_
    def get_first(s):
        if s not in first: first[s] = []
        return first[s]
    def get_follow(s):
        if s not in follow: follow[s] = []
        return follow[s]

    def union(v, s):
        if isinstance(s, list):
            if len(s) > 0:
                difference = list(np.setdiff1d(s, v))
                if len(difference) > 0:
                    v.extend(difference)
                    return True
        else:
            if not s in v:
                v.append(s)
                return True
        return False
        

    # Compute Nullable Table
    changed = True
    while(changed):
        changed = False
        for rule in productionRules:
            if not nullable[rule[0]]:
                if len(rule) == 1 or all(is_nullable(s) for s in rule[1:]):
                    nullable[rule[0]] = True
                    changed = True

    if verbose:
        print("Nullable:\n    ", end="")
        print("\n    ".join(f"{A}: {nullable[A]}" for A in nullable if A in nonterminals), "\n")

    # Compute First Table
    changed = True
    while(changed):
        changed = False
        for rule in productionRules:
            for s in rule[1:]:
                if s in terminals:
                    changed = changed or union(get_first(rule[0]), s)
                    break
                else:
                    changed = changed or union(get_first(rule[0]), get_first(s))
                    if not is_nullable(s): break

    if verbose:
        print("First:\n    ", end="")
        print("\n    ".join(f"{s}: {first[s]}" for s in first), "\n")

    def first_star(rule, i):
        result = []
        for j in range(i, len(rule)):
            if rule[j] in nonterminals:
                union(result, get_first(rule[j]))
                if not is_nullable(rule[j]): break
            else:
                union(result, rule[j])
                break

        return result

    # Compute Follow Table
    changed = True
    while(changed):
        changed = False
        for rule in productionRules:
            for j in range(1, len(rule)):
                if rule[j] in nonterminals:
                    firstS = first_star(rule, j+1)
                    changed = changed or union(get_follow(rule[j]), firstS)
                    if all(is_nullable(rule[k]) for k in range(j+1, len(rule))):
                        changed = changed or union(get_follow(rule[j]), get_follow(rule[0]))

    if verbose:
        print("Follow:\n    ", end="")
        print("\n    ".join(f"{s}: {follow[s]}" for s in follow), "\n")

    ###############################################################################################

    class Item:
        def __init__(self, rule=0, bookmark=1, item=None):
            if item is not None:
                self.rule = item.rule
                self.bookmark = item.bookmark+1
            else:
                self.rule = rule
                self.bookmark = bookmark

            self.follow = {}
        
        def __str__(self):
            return " ".join(productionRules[self.rule][:self.bookmark]+["⋅"]+productionRules[self.rule][self.bookmark:])

        def __hash__(self):
            return hash(str(self))

        def get_rule(self):
            return productionRules[self.rule]

        def get_next(self, i=0):
            return productionRules[self.rule][self.bookmark+i]

    class State:
        state_map = {}
        num = 0

        def __init__(self, *items):
            self.items = list(items)
            self.transitions = {}
            self.num = State.num
            self.visited = False
            State.num += 1

        def reset_visited(self):
            if self.visited:
                self.visited = False
                for transition, state in self.transitions.items():
                    state.reset_visited()

        def add_item(self, item):
            self.items.append(item)

        def generate_items(self):
            for item in self.items:
                if item.bookmark < len(item.get_rule()):
                    next_item = item.get_next()
                    if next_item in nonterminals:
                        for rule in productions[next_item]:
                            if not any(rule == i.rule for i in self.items):
                                self.items.append(Item(rule))

                        # if item.bookmark+1 < len(item.get_rule()) and is_nullable(next_item):
                        #     next_item = item.get_next(1)
                        #     if next_item in nonterminals:
                        #         for rule in productions[next_item]:
                        #             if not any(rule == i.rule for i in self.items):
                        #                 self.items.append(Item(rule))


        def generate_states(self):
            if not self.visited:
                self.visited = True
                self.generate_items()

                def add_transition(new_item, next_item):
                    if next_item in self.transitions:
                        self.transitions[next_item].add_item(new_item)
                    else:
                        hashed = hash(new_item)
                        if hashed in State.state_map:
                            self.transitions[next_item] = State.state_map[hashed]
                        else:
                            self.transitions[next_item] = State(new_item)
                            State.state_map[hashed] = self.transitions[next_item]
                        
                for item in self.items:

                    new_item = Item(item=item)
                    if item.bookmark < len(item.get_rule()):
                        add_transition(new_item, item.get_next())
                    # else:
                    #     for next_item in get_follow(item.get_rule()[0]):
                    #         add_transition(next_item)

                for transition, state in self.transitions.items():
                    state.generate_states()

        def get_transitions(self):
            transitions = []
            if not self.visited:
                self.visited = True
                for transition, state in self.transitions.items():
                    transitions.append([self.num, transition, "SHIFT", state.num])
                    transitions.extend(state.get_transitions())
                for item in self.items:
                    if item.bookmark >= len(item.get_rule()):
                        for s in get_follow(item.get_rule()[0]):
                            transitions.append([self.num, s, "REDUCE", item.rule])

            return transitions

        def print(self):
            if not self.visited:
                self.visited = True
                print(f"State {self.num}:\n    ", end="")
                print("\n    ".join(list(map(str, self.items))))
                print("    Transitions: "+", ".join(f"{t}->{s.num}" for t, s in self.transitions.items()))

                for transition, state in self.transitions.items():
                    state.print()


    state = State(Item(start_state))
    state.reset_visited()
    state.generate_states()

    if verbose:
        state.reset_visited()
        state.print()


    state.reset_visited()
    transitions = state.get_transitions()
    transitions.sort(key=lambda x: x[0])
    # print("\n".join(" ".join(map(str, t)) for t in transitions))
    # exit(1)


    terminals.sort()
    nonterminals.sort()

    with open(outfile, "w") as file:
        file.write(f"{len(terminals)}\n")
        file.write("\n".join(terminals)+"\n")
        file.write(f"{len(nonterminals)}\n")
        file.write("\n".join(nonterminals)+"\n")
        file.write(f"start\n")
        file.write(f"{len(productionRules)}\n")
        file.write("\n".join([" ".join(rule) for rule in productionRules])+"\n")
        file.write(f"{State.num}\n")
        file.write(f"{len(transitions)}\n")
        file.write("\n".join(" ".join(map(str, t)) for t in transitions)+"\n")


if __name__ == "__main__":
    parseLR1("../LanguageSpecification.yml", "../LanguageSpecification.lr1")