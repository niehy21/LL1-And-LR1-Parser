#include "TokenDict.h"
#include <string>
#include <cstring>

static const int TOKEN_NUMBER = 17;

static const int tokens[TOKEN_NUMBER] = {
    '+', '-', '*', '/',
    ';',
    '>', '<',
    '=',
    '(', ')',
    '{', '}',
    EQUAL,          // For "==". 256 > 255 avoids illegal unsigned char cast to int
    IDENTIFIER,     // For "identifier"
    NUMBER,         // For "number"
    STRING_LITERAL, // For "string_literal"
    UNIDENTIFIED    // For "unidentified"
};

static const Token::TokenTag tags[TOKEN_NUMBER] = {
    "plus", "minus", "multiply", "divide",
    "semicolon",
    "greater", "less",
    "assign",
    "lparen", "rparen",
    "lbrace", "rbrace",
    "equal",
    "identifier",
    "number",
    "string_literal",
    "unidentified"
};

TokenDict::TokenDict() {
    for (int i = 0; i < TOKEN_NUMBER; i++) {
        dict[tokens[i]] = tags[i];
    }
}