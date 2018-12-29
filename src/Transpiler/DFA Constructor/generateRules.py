import yaml

with open("../LanguageSpecification.yml", "r") as file:
    specs = yaml.load(file)

    print(specs)