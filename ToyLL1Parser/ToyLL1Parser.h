#pragma once

#include "../ToyLexer/ToyLexer.h"
#include "../ToySyntaxer/ToySyntaxer.h"
#include "../ToyAST/ToyAST.h"
#include "LL1Table.h"
#include <string>
#include <map>
#include <set>
#include <stack>
#include <queue>

struct ToyLL1Parser {
    LL1Table table;

    // 在构造函数中完成 LL(1) 分析表的构造
    // 表为映射，若键不在映射中，即出错标志
    ToyLL1Parser(
        ToySyntaxer &syntaxer
    ) {
        // production: A → α1 | α2 | ...
        for (const auto production : syntaxer.productions) {
            const auto &A = production.first;
            // rhsSymbolLists: α1 | α2 | ...
            const auto &rhsSymbolLists = production.second;
            // AFirst: First(A)
            const auto AFirst = syntaxer.getFirstSet(A);
            // a: a ∈ First(A)
            for (const auto &a : AFirst) {
                // Find αk s.t. a ∈ First(αk)
                for (const auto &alpha : rhsSymbolLists) {
                    const auto rhsFirst = syntaxer.getFirstSet(alpha);
                    if (rhsFirst.find(a) != rhsFirst.end()) {
                        // M[A, a] = A → αk
                        table[std::pair<Symbol, Symbol>(A, a)] = Production(A, alpha);
                        break;
                    }
                }
                // $ ∈ First(A)
                if (a == "$") {
                    // ∀b ∈ Follow(A)
                    const auto AFollow = syntaxer.getFollowSet(A);
                    for (const auto &b : AFollow) {
                        // M[A, b] = A → $
                        Symbol bt = (b == "#") ? "$" : b;
                        table[std::pair<Symbol, Symbol>(A, bt)] = Production(A, SymbolList({ "$" }));
                    }
                }
            }
        }
    }

    ToyAST run(const TokenList &tokenList);

    std::string writeLL1Table(const ToySyntaxer &syntaxer);
};
