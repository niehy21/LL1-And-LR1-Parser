#include "TokenList.h"

std::string to_string(const TokenList &list) {
    std::string buf;
    for (const auto &token : list) {
        buf += to_string(token) + "\n";
    }
    return buf;
}

std::ostream &operator<<(std::ostream &os, const TokenList &list)
{
    for (const auto &token : list) {
        os << token << std::endl;
    }
    return os;
}