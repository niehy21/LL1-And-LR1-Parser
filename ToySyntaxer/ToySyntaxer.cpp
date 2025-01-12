#include "ToySyntaxer.h"
#include <cstring>
#include <algorithm>
#include <iostream>
// #include <iostream>
static std::string trim(std::string &str) {
    if (str.empty()) {
        return str;
    }
    str.erase(0, str.find_first_not_of(" \r\n\t"));
    str.erase(str.find_last_not_of(" \r\n\t") + 1);
    return str;
}

static std::vector<std::string> split(const std::string &str, const std::string &delim) {
    std::vector<std::string> lines;
    char *s = new char[str.length() + 1];
    strcpy(s, str.c_str());
    char *d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());
    char *p = strtok(s, d);
    while (p) {
        lines.push_back(std::string(p));
        p = strtok(NULL, d);
    }
    delete[] s;
    delete[] d;
    return lines;
}

void ToySyntaxer::parseGrammar(const std::string &grammar) {
    auto lines = split(grammar, "\n");
    auto findStartSymbol = false;
    for (auto &line : lines) {
        // 跳过空行
        if (trim(line).empty()) {
            continue;
        }

        // 拆分左右
        auto lineTuple = split(line, "->");
        Symbol lhs = trim(lineTuple[0]);
        nonterminalSymbols.insert(lhs);
        auto rhs = split(lineTuple[1], "|");

        // 创建映射
        if (productions.find(lhs) == productions.end()) {
            productions[lhs] = {};
        }

        // 开始符号
        if (!findStartSymbol) {
            findStartSymbol = true;
            startSymbol = lhs;
        }

        // 处理右部
        for (auto &rhsSymbolList : rhs) {
            auto symbols = split(trim(rhsSymbolList), " ");
            SymbolList symbolList;

            // 去除空项
            auto iter = symbols.begin();
            while (iter != symbols.end()) {
                if ((*iter) == "") {
                    iter = symbols.erase(iter);
                } else {
                    Symbol symbol(*iter);
                    symbolList.emplace_back(*iter);
                    if (symbol.isTerminal()) {
                        terminalSymbols.insert(symbol);
                    } else {
                        nonterminalSymbols.insert(symbol);
                    }
                    iter++;
                }
            }
            productions[lhs].insert(symbolList).second;
        }
    }
    nonterminalSymbols.insert("S'");
    productions["S'"] = {{ startSymbol }};
    areFollowSetsComputed = false;
}

SymbolSet ToySyntaxer::getFirstSet(const Symbol &symbol) {
    return getFirstSet(SymbolList({ symbol }));
}

SymbolSet ToySyntaxer::getFirstSet(const SymbolList &symbolList) {
    if (symbolList.empty()) {
        return { "$" };
    }
    auto symbol = symbolList[0];
    if (symbolList.size() == 1 && firstSets.find(symbol) != firstSets.end()) {
        return firstSets[symbol];
    }
    SymbolSet firstSet;
    // 非终结符
    if (!symbol.isTerminal()) {
        for (const auto &rhs : productions[symbol]) {
            if (rhs[0] != "$") {
                auto subFirstSet = getFirstSet(rhs);
                for (const auto &s : subFirstSet) {
                    firstSet.insert(s);
                }
            } else {
                if (symbolList.size() == 1) {
                    firstSet.insert("$");
                } else {
                    auto subSymbolList = SymbolList(symbolList.begin() + 1,
                        symbolList.end());
                    auto subFirstSet = getFirstSet(subSymbolList);
                    for (const auto &s : subFirstSet) {
                        firstSet.insert(s);
                    }
                }
            }
        }
    // 终结符
    } else {
        firstSet.insert(symbol);
    }

    // 更新单个符号的 First 集
    if (symbolList.size() == 1) {
        firstSets[symbol] = firstSet;
    }

    return firstSet;
}

bool ToySyntaxer::getFollowSetsKernel(const int epoch) {
    bool changed = false;
    for (const auto &production : productions) {
        const auto &A = production.first;
        const auto &rhsSymbolLists = production.second;
        if (A == "S'") {
            changed |= followSets["S'"].insert("#").second;
            changed |= followSets[startSymbol].insert("#").second;
        } else {
            for (const auto &rhs : rhsSymbolLists) {
                // A → αBβ, First(β) - {$} 加入
                if (!epoch) {
                    for (auto iter = rhs.begin(); iter != rhs.end() - 1; iter++) {
                        if (iter->isTerminal()) {
                            continue;
                        }
                        SymbolList beta(iter + 1, rhs.end());
                        auto betaFirst = getFirstSet(beta);
                        bool impliesEmpty = false;
                        for (const auto &symbol : betaFirst) {
                            if (symbol != "$") {
                                changed |= followSets[*iter].insert(symbol).second;
                            }
                        }
                    }
                }

                // A → αB, Follow(A) 加入
                auto endSymbol = *(rhs.end() - 1);
                if (!endSymbol.isTerminal()) {
                    for (const auto &symbol : followSets[A]) {
                        changed |= followSets[endSymbol].insert(symbol).second;
                    }
                }

                // A → αBβ 且 β⇒*$, Follow(A) 加入
                for (auto iter = rhs.begin(); iter != rhs.end() - 1; iter++) {
                    if (iter->isTerminal()) {
                        continue;
                    }
                    SymbolList beta(iter + 1, rhs.end());
                    auto betaFirst = getFirstSet(beta);
                    if (betaFirst.find("$") != betaFirst.end()) {
                        for (const auto &symbol : followSets[A]) {
                            changed |= followSets[*iter].insert(symbol).second;
                        }
                    }
                }
            }
        }
    }

    return changed;
}

void ToySyntaxer::getFollowSets() {
    for (int epoch = 0; getFollowSetsKernel(epoch); epoch++) {
    }
    areFollowSetsComputed = true;
}

SymbolSet ToySyntaxer::getFollowSet(const Symbol &symbol) {
    if (!areFollowSetsComputed) {
        getFollowSets();
    }
    return followSets[symbol];
}
