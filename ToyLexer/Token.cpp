#include "Token.h"

std::string to_string(const Token &token) {
    return "('" + token.tag + "', '" + token.value + "')";
}

std::ostream &operator<<(std::ostream &os, const Token &token)
{
    return (os << to_string(token));
}