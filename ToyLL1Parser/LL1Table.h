#pragma once
#include "../ToySyntaxer/ToySyntaxer.h"
#include <utility>
#include <map>
using LL1Item = Production;
using LL1Table = std::map<std::pair<Symbol, Symbol>, LL1Item>;