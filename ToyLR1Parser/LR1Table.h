#pragma once

#include "../ToySyntaxer/ToySyntaxer.h"
#include <iostream>
#include <set>
#include <map>
#include <utility>

// A -> α.β, a
struct LR1Item {
    // A -> αβ
    Production p;

    // Position of the dot
    std::size_t dot;

    // a
    Symbol lookahead;

    LR1Item(
        const Production &_p,
        const std::size_t _dot,
        const Symbol &_lookahead
    ) : p(_p),
        dot(_dot),
        lookahead(_lookahead) {
    }

    // Judge same
    bool operator==(const LR1Item &item) const;

    bool operator<(const LR1Item &item) const;

    friend std::ostream &operator<<(std::ostream &os, const LR1Item &item);
};

extern std::string to_string(const LR1Item &item);

enum ActionType {
    SHIFT,
    REDUCE,
    ACCEPT
};

struct Action {
    ActionType type;

    // type == SHIFT, id of state
    // type == REDUCE, id of production
    std::size_t to;

    Action(
        const ActionType _type = ACCEPT,
        const std::size_t _to = 0xffffffff
    ) : type(_type),
        to(_to) {
    }
};

// LR(1) items collection, e.g. I₀, I₁, ...
struct LR1State {
    std::set<LR1Item> items;

    LR1State &getClosure(ToySyntaxer &syntaxer);

    bool operator==(const LR1State &state) const;
};

using ActionTable = std::map<std::tuple<Symbol, std::size_t>, Action>;
using GotoTable = std::map<std::tuple<Symbol, std::size_t>, std::size_t>;

struct LR1Table {
    ActionTable actions;
    GotoTable gotos;
};
