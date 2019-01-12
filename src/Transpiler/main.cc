
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

void runTests() {
    assertScan("int main { return 5; }", "int⋮ ⋮main⋮ ⋮{⋮ ⋮return⋮ ⋮5⋮;⋮ ⋮}");
    assertScan("int main2 { return 5; }", "int⋮ ⋮main2⋮ ⋮{⋮ ⋮return⋮ ⋮5⋮;⋮ ⋮}");
    assertScan(
        "int main    { int x_1 = 5.6; return x_1; }",
        "int⋮ ⋮main⋮    ⋮{⋮ ⋮int⋮ ⋮x_1⋮ ⋮=⋮ ⋮5.6⋮;⋮ ⋮return⋮ ⋮x_1⋮;⋮ ⋮}");
    assertScan("int main { return 5+6/7; }",
               "int⋮ ⋮main⋮ ⋮{⋮ ⋮return⋮ ⋮5⋮+⋮6⋮/⋮7⋮;⋮ ⋮}");
    assertScan("int main { return (5+6)/7; }",
               "int⋮ ⋮main⋮ ⋮{⋮ ⋮return⋮ ⋮(⋮5⋮+⋮6⋮)⋮/⋮7⋮;⋮ ⋮}");
    assertScan("int main { int* x; x->5; }",
               "int⋮ ⋮main⋮ ⋮{⋮ ⋮int⋮*⋮ ⋮x⋮;⋮ ⋮x⋮->⋮5⋮;⋮ ⋮}");
    assertScan("int main { string x = \"asd \"; }",
               "int⋮ ⋮main⋮ ⋮{⋮ ⋮string⋮ ⋮x⋮ ⋮=⋮ ⋮\"⋮asd⋮ ⋮\"⋮;⋮ ⋮}");
    assertScan("int main { string x = f\"asd{x}\"; }",
               "int⋮ ⋮main⋮ ⋮{⋮ ⋮string⋮ ⋮x⋮ ⋮=⋮ ⋮f⋮\"⋮asd⋮{⋮x⋮}⋮\"⋮;⋮ ⋮}");
}

int main(int argc, char** argv) {
    try {
        // runTests();
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
        Parser parser{"./LanguageSpecification.lr1"};
        // cout << parser << endl;
        unique_ptr<ParseTree> tree = parser.parse("int main() { return 5; }");
    } catch (const char* err) {
        cerr << err << endl;
    } catch (const string& err) {
        cerr << err << endl;
    }
}
