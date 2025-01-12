#include "Symbol.h"

std::size_t SymbolHash::operator()(const Symbol &s) const {
    return std::hash<std::string>()(s);
}
