#pragma once

#include "Symbol.h"
#include <string>

// 单个产生式
struct Production {
    Symbol lhs;
    SymbolList rhs;

    Production(
        const Symbol &_lhs = "",
        const SymbolList &_rhs = SymbolList()
    ) : lhs(_lhs),
        rhs(_rhs) {
    }

    // Production &operator=(const Production &p);

    bool operator==(const Production &p) const;

    bool operator<(const Production &p) const;

    friend std::ostream &operator<<(std::ostream &os, const Production &p);
};

extern std::string to_string(const Production &p);