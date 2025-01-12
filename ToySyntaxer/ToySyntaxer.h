#pragma once

#include <vector>
#include <string>
#include <map>
#include <set>
#include "Symbol.h"
#include "Production.h"
#include "FirstSet.h"
#include "FollowSet.h"

struct ToySyntaxer {
    std::map<Symbol, std::set<SymbolList>> productions;
    Symbol startSymbol;
    SymbolSet terminalSymbols, nonterminalSymbols;
    FirstSetMap firstSets;
    FollowSetMap followSets;
    bool areFollowSetsComputed = false;

    // 解析以换行分割的多个产生式文法，生成开始符号和产生式集
    void parseGrammar(const std::string &grammar);
    // 计算一个符号的 First 集
    SymbolSet getFirstSet(const Symbol &symbol);
    // 计算一串符号的 First 集
    SymbolSet getFirstSet(const SymbolList &symbolList);
    // 计算所有非终结符 Follow 集的核心步骤
    // 对每个产生式都作此操作，并不断迭代至收敛
    bool getFollowSetsKernel(const int epoch);
    // 计算所有非终结符 Follow 集
    void getFollowSets();
    // 计算单个非终结符 Follow 集
    SymbolSet getFollowSet(const Symbol &symbol);
};