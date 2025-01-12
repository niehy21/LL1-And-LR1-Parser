#pragma once
#include "Token.h"
#include <vector>
#include <iostream>
class TokenList : public std::vector<Token> {
public:
    friend std::string to_string(const TokenList &list);
    friend std::ostream &operator<<(std::ostream &os, const TokenList &list);
};
