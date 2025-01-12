#pragma once
#include <vector>
#include <string>
#include <set>
#include <cctype>
class Symbol : public std::string {
public:
    Symbol(const std::string &str) : std::string(str) {
    }

    Symbol(const char *str = "") : std::string(str) {
    }

    // 首字母大写，则为非终结符，否则为终结符
    inline bool isTerminal() const {
        return !isupper((*this)[0]);
    }
};
class SymbolHash {
public:
    std::size_t operator()(const Symbol &s) const;
};
using SymbolList = std::vector<Symbol>;
using SymbolSet = std::set<Symbol>;