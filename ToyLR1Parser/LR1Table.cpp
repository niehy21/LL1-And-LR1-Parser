#include "LR1Table.h"

#include <queue>

bool LR1Item::operator==(const LR1Item &item) const {
    return item.p == p && item.dot == dot && item.lookahead == lookahead;
}

bool LR1Item::operator<(const LR1Item &item) const {
    return (item.p < p) || 
        (item.p == p && (item.dot < dot ||
        (item.dot == dot && item.lookahead < lookahead)));
}

std::ostream &operator<<(std::ostream &os, const LR1Item &item) {
    return (os << to_string(item));
}

std::string to_string(const LR1Item &item) {
    std::string buf = item.p.lhs + " -> ";
    auto split = std::min(item.dot, item.p.rhs.size());
    for (int i = 0; i < split; i++) {
        buf += item.p.rhs[i] + " ";
    }
    buf += ".";
    for (int i = split; i < item.p.rhs.size(); i++) {
        buf += " " + item.p.rhs[i];
    }
    buf += ", " + item.lookahead;
    return buf;
}

LR1State &LR1State::getClosure(ToySyntaxer &syntaxer) {
    // 待处理项目队列
    std::queue<LR1Item> todos;
    for (const auto &item : items) {
        todos.emplace(item);
    }

    while (!todos.empty()) {
        auto todo = todos.front();
        todos.pop();

        // 规约项目，跳过
        // A -> α.
        if (todo.dot >= todo.p.rhs.size()) {
            continue;
        }

        auto B = todo.p.rhs[todo.dot];
        // 待约项目, 展开求闭包
        // A -> α.Bβ, a
        if (!B.isTerminal()) {
            SymbolList beta(
                todo.p.rhs.begin() + todo.dot + 1,
                todo.p.rhs.end()
            );
            // βa, First(βa) 用于求新项目的 lookahead
            beta.emplace_back(todo.lookahead);
            auto betaFirst = syntaxer.getFirstSet(beta);
            for (const auto &rhs : syntaxer.productions[B]) {
                for (const auto &lookahead : betaFirst) {
                    LR1Item item(Production(B, rhs), 0, lookahead);
                    if (items.find(item) == items.end()) {
                        items.emplace(item);
                        todos.emplace(item);
                    }
                }
            }
        }
    }

    return *this;
}

bool LR1State::operator==(const LR1State &state) const {
    return items == state.items;
}
