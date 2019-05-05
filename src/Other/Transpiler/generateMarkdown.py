import yaml

with open("./LanguageSpecification.yml", "r") as file:
    specs = yaml.load(file)



with open("./README.md", "w") as file:
    def write(s):
        file.write(s)
        # print(s, end="")

    write("# Language Specification\n\n")
    write("## Lexical Syntax\n\n")
    write("A procedure definition is a sequence of *tokens* optionally separated by *white space* consisting of spaces, newlines, or comments. Every valid token is one of the following:\n\n")

    for token in specs["tokens"]:
        for key in token:
            description = token[key]['description'] if 'description' in token[key] else f"the string \"{token[key]['lexeme']}\""
            write(f" * `{key}`: {description}\n")

    write("\nIn addition to the above tokens, the following are also valid tokens and their strings are reserved keywords:\n\n")

    for keyword in specs["keywords"]:
        for key in keyword:
            write(f" * `{key}`: the string \"{keyword[key]['lexeme']}\"\n")

    write("\nWhite space consists of any sequence of the following:\n\n")

    for whitespace in specs["whitespace"]:
        for key in whitespace:
            write(f" * `{key}`: {whitespace[key]['description']}\n")

    write("\n## Context-free Syntax\n\n")
    write("A context-free grammar for a valid CML program is:\n\n")
    write(" * terminal symbols: the set of valid tokens above\n")
    write(" * nonterminal symbols:\n")
    
    for symbol in specs["nonterminalSymbols"]:
        write(f"   * `{symbol}`\n")

    write(f" * start symbol: `{specs['startSymbol']}`\n")
    write(" * production rules:\n")
    
    for rule in specs["productionRules"]:
        symbols = rule.split(" ")
        write(f"   * `{symbols[0]} → {' '.join(symbols[1:])}`\n")
