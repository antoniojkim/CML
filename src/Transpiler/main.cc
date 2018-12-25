
#include <assert.h>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include "scanner.h"

using namespace std;

ostream& operator<<(ostream& out, list<Token> tokens){
    bool first = true;
    for (auto& token : tokens) {
        if (first) {
            first = false;
        }
        else{
            out << "⋮";
        }
        out << token.lexeme;
        // cout << token.lexeme << "  " << getTypeString(token.type) << endl;
    }
    return out;
}

void assertScan(const string& input, const string& expected) {
    list<Token> tokens;
    scan(input, tokens);
    ostringstream oss;
    oss << tokens;
    if (oss.str() != expected) {
        cout << oss.str() << " != " << expected << endl;
        assert(oss.str() == expected);
    }
}

void runTests() {
    assertScan("int main { return 5; }", "int⋮ ⋮main⋮ ⋮{⋮ ⋮return⋮ ⋮5⋮;⋮ ⋮}");
    assertScan("int main2 { return 5; }", "int⋮ ⋮main2⋮ ⋮{⋮ ⋮return⋮ ⋮5⋮;⋮ ⋮}");
    assertScan("int main    { int x_1 = 5.6; return x_1; }", "int⋮ ⋮main⋮    ⋮{⋮ ⋮int⋮ ⋮x_1⋮ ⋮=⋮ ⋮5.6⋮;⋮ ⋮return⋮ ⋮x_1⋮;⋮ ⋮}");
    assertScan("int main { return 5+6/7; }", "int⋮ ⋮main⋮ ⋮{⋮ ⋮return⋮ ⋮5⋮+⋮6⋮/⋮7⋮;⋮ ⋮}");
    assertScan("int main { return (5+6)/7; }", "int⋮ ⋮main⋮ ⋮{⋮ ⋮return⋮ ⋮(⋮5⋮+⋮6⋮)⋮/⋮7⋮;⋮ ⋮}");
    assertScan("int main { int* x; x->5; }", "int⋮ ⋮main⋮ ⋮{⋮ ⋮int⋮*⋮ ⋮x⋮;⋮ ⋮x⋮->⋮5⋮;⋮ ⋮}");
    assertScan("int main { string x = \"asd \"; }", "int⋮ ⋮main⋮ ⋮{⋮ ⋮string⋮ ⋮x⋮ ⋮=⋮ ⋮\"⋮asd⋮ ⋮\"⋮;⋮ ⋮}");
    assertScan("int main { string x = f\"asd{x}\"; }", "int⋮ ⋮main⋮ ⋮{⋮ ⋮string⋮ ⋮x⋮ ⋮=⋮ ⋮f⋮\"⋮asd⋮{⋮x⋮}⋮\"⋮;⋮ ⋮}");
}

int main(int argc, char** argv) {
    runTests();
    if (argc < 3) {
        cerr << "Invalid Usage:  Expected    ./CML <cml input file> <c output file>" << endl;
        return 1;
    }
    string cmlFile{argv[1]};
    string cFile{argv[2]};
    
    cout << cmlFile << endl;

    ifstream cmlFileIn(cmlFile);
    ostringstream input;
    string s;
    while (getline(cmlFileIn, s)){
        input << s << endl;
    }
    cout << input.str() << endl;
    list<Token> tokens;
    scan(input.str(), tokens);
    cout << tokens << endl;
}
