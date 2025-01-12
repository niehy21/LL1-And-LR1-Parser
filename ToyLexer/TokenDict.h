#pragma once
#include "Token.h"

enum {
    EQUAL = 256,
    IDENTIFIER,
    NUMBER,
    STRING_LITERAL,
    UNIDENTIFIED
};

class TokenDict {
private:
    // Token 与 Token 名的映射
    // e.g., dict['='] == "assign"
    Token::TokenTag dict[261];

public:
    TokenDict();
    inline Token::TokenTag operator[](const int id) const {
        return dict[id];
    }

    inline Token::TokenTag operator[](const char id) const {
        return (*this)[(const unsigned char)id];
    }
};