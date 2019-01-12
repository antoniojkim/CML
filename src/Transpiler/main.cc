
#include <assert.h>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include "Parser/parser.h"
#include "Scanner/scanner.h"

using namespace std;

void assertScan(const string& input, const string& expected) {
    list<Token> tokens;
    scan(input, tokens);
    ostringstream oss;
    print(oss, tokens, "⋮");
    if (oss.str() != expected) {
        cout << oss.str() << " != " << expected << endl;
        assert(oss.str() == expected);
    }
}

void assertParsable(Parser& parser, const string& input,
                    const bool& printTree = false) {
    unique_ptr<ParseTree> tree = parser.parse(input);
    if (printTree) {
        tree->print(cout) << endl;
    }
}

void assertUnparsable(Parser& parser, const string& input) {
    try {
        unique_ptr<ParseTree> tree = parser.parse(input);
    } catch (...) {
        return;
    }
    throw "ERROR:  " + input + "  is parsable";
}

void runTests() {
    assertScan("int main { return 5; }", "int⋮main⋮{⋮return⋮5⋮;⋮}");
    assertScan("int main2 { return 5; }", "int⋮main2⋮{⋮return⋮5⋮;⋮}");
    assertScan("int main    { int x_1 = 5.6; return x_1; }",
               "int⋮main⋮{⋮int⋮x_1⋮=⋮5.6⋮;⋮return⋮x_1⋮;⋮}");
    assertScan("int main { return 5+6/7; }", "int⋮main⋮{⋮return⋮5⋮+⋮6⋮/⋮7⋮;⋮}");
    assertScan("int main { return (5+6)/7; }",
               "int⋮main⋮{⋮return⋮(⋮5⋮+⋮6⋮)⋮/⋮7⋮;⋮}");
    assertScan("int main { int* x; x->5; }", "int⋮main⋮{⋮int⋮*⋮x⋮;⋮x⋮->⋮5⋮;⋮}");
    assertScan("int main { string x = \"asd \"; }",
               "int⋮main⋮{⋮string⋮x⋮=⋮\"⋮asd ⋮\"⋮;⋮}");
    assertScan("int main { string x = f\"asd{x}\"; }",
               "int⋮main⋮{⋮string⋮x⋮=⋮f⋮\"⋮asd⋮{⋮x⋮}⋮\"⋮;⋮}");

    Parser parser{"./LanguageSpecification.lr1"};
    assertParsable(parser, "int main() { return 5; }");
    assertParsable(parser, "int main() { return s5; }");
    assertUnparsable(parser, "int main() { return 5s; }");
    assertParsable(parser, "int main() { return \"hello world\"; }");
    assertParsable(parser, "int main() { return f\"hello world\"; }");

    cout << endl << "All Tests Passed!" << endl << endl;
}

int main(int argc, char** argv) {
    try {
        runTests();
        // if (argc < 3) {
        //     cerr << "Invalid Usage:  Expected    ./CML <cml input file> <c
        //     output file>" << endl; return 1;
        // }
        // string cmlFile{argv[1]};
        // string cFile{argv[2]};

        // cout << cmlFile << endl;

        // ifstream cmlFileIn(cmlFile);
        // ostringstream input;
        // string s;
        // while (getline(cmlFileIn, s)){
        //     input << s << endl;
        // }
        // cout << input.str() << endl;
        // list<Token> tokens;
        // scan(input.str(), tokens);
        // cout << tokens << endl;
        // cout << parser << endl;
    } catch (const char* err) {
        cerr << err << endl;
    } catch (const string& err) {
        cerr << err << endl;
    }
}
