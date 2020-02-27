
types = (
    ("std::int8_t",        "int8"),
    ("short int",          "int16"),
    ("int",                "int32"),
    ("long long",          "int64"),
    ("std::uint8_t",       "uint8"),
    ("unsigned short int", "uint16"),
    ("unsigned int",       "uint32"),
    ("unsigned long long", "uint64"),
    ("float",              "float32"),
    ("double",             "float64"),
)

for T, _1 in types:
    for U, _2 in types:
        print(f"template Array<{T}>::Array(std::initializer_list<{U}>);")