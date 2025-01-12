#include "Production.h"

#include <iostream>

// Production &Production::operator=(const Production &p) {
//     lhs = p.lhs;
//     rhs = p.rhs;
//     return (*this);
// }

std::ostream &operator<<(std::ostream &os, const Production &p) {
    return (os << to_string(p));
}

std::string to_string(const Production &p) {
    std::string buf;
    buf += p.lhs + " -> " + p.rhs[0];
    for (auto iter = p.rhs.begin() + 1; iter != p.rhs.end(); iter++) {
        buf += " " + (*iter);
    }
    return buf;
}

bool Production::operator==(const Production &p) const {
    return p.lhs == lhs && p.rhs == rhs;
}

bool Production::operator<(const Production &p) const {
    return p.lhs < lhs || (p.lhs == lhs && p.rhs < rhs);
}
