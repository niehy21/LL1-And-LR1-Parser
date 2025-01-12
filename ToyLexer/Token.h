#pragma once
#include <string>
#include <iostream>
struct Token {
    using TokenTag   = std::string;
    using TokenValue = std::string;

    // 对于单字符 Token，直接使用 ASCII 值
    // 实际上是为了方便将 ASCII 映射到 tag
    int id;

    // Token 名称
    TokenTag tag;

    // Token 内容
    TokenValue value;

    Token(const int _id, const TokenTag &_tag, const TokenValue &_value) :
        id(_id),
        tag(_tag),
        value(_value) {
    }
    friend std::string to_string(const Token &token);
    friend std::ostream &operator<<(std::ostream &os, const Token &token);
};