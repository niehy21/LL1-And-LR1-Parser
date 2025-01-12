// #include "ToyLexer/ToyLexer.h"
#include "ToyFileIO/ToyFileIO.h"
#include "ToySyntaxer/ToySyntaxer.h"
#include <iostream>
#include <map>
using namespace std;

int main(void) {
    std::string grammar = "\
        E -> T E'\n\
        E' -> + T E' | $\n\
        T -> F T'\n\
        T' -> * F T' | $\n\
        F -> ( E ) | i\
    ";
    std::map<Symbol, SymbolSet> expectedFirst, expectedFollow;
    expectedFirst["S'"] = { "(", "i" };
    expectedFirst["E"] = { "(", "i" };
    expectedFirst["E'"] = { "+", "$" };
    expectedFirst["T"] = { "(", "i" };
    expectedFirst["T'"] = { "*", "$" };
    expectedFirst["F"] = { "(", "i" };
    expectedFollow["S'"] = { "#" };
    expectedFollow["E"] = { "#", ")" };
    expectedFollow["E'"] = { "#", ")" };
    expectedFollow["T"] = { "#", "+", ")" };
    expectedFollow["T'"] = { "#", "+", ")" };
    expectedFollow["F"] = { "#", "+", "*", ")" };
    ToySyntaxer syntaxer;
    
    cout << "Running tests of First and Follow sets..." << endl;
    syntaxer.parseGrammar(grammar);

    for (const auto &nonterminal : syntaxer.nonterminalSymbols) {
        auto calculatedFirst = syntaxer.getFirstSet(nonterminal);
        if (expectedFirst[nonterminal] != calculatedFirst) {
            cout << "Calculated First(" << nonterminal << ") = { " << *calculatedFirst.cbegin();
            for (auto iter = ++calculatedFirst.cbegin();
                iter != calculatedFirst.cend();
                iter++) {
                cout << ", " << *iter;
            }
            cout << " }, while { " << *expectedFirst[nonterminal].cbegin();
            for (auto iter = ++expectedFirst[nonterminal].cbegin();
                iter != expectedFirst[nonterminal].cend();
                iter++) {
                cout << ", " << *iter;
            }
            cout << " } is expected!" << endl;
            exit(EXIT_FAILURE);
        }
    }

    cout << "Success!" << endl;

    for (const auto &nonterminal : syntaxer.nonterminalSymbols) {
        auto calculatedFollow = syntaxer.getFollowSet(nonterminal);
        if (expectedFollow[nonterminal] != calculatedFollow) {
            cout << "Calculated Follow(" << nonterminal << ") = { " << *calculatedFollow.cbegin();
            for (auto iter = ++calculatedFollow.cbegin();
                iter != calculatedFollow.cend();
                iter++) {
                cout << ", " << *iter;
            }
            cout << " }, while { " << *expectedFollow[nonterminal].cbegin();
            for (auto iter = ++expectedFollow[nonterminal].cbegin();
                iter != expectedFollow[nonterminal].cend();
                iter++) {
                cout << ", " << *iter;
            }
            cout << " } is expected!" << endl;
            exit(EXIT_FAILURE);
        }
    }

    cout << "Success!" << endl;

    return 0;
}