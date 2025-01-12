#pragma once
#include "Token.h"
#include "TokenDict.h"
#include "TokenList.h"
#include "KeywordList.h"
#include <cstdio>
#include <string>

class ToyLexer {
private:
    const TokenDict tokenDict;
    TokenList tokenList;
    KeywordList keywordList;
    
    inline bool isTaggedDelimiter(const char c) {
        return (
            c == '+' || c == '-' ||
            c == '*' || c == '/' ||
            c == ';' || c == '=' ||
            c == '>' || c == '<' ||
            c == '(' || c == ')' ||
            c == '{' || c == '}'
        );
    }

    bool isDelimiter(const char c);

    bool isIdentifierRest(const char *str);

    bool isIdentifier(const char *str);

    bool isNumberRest(const char *str);
    
    bool isNumber(const char *str);
    
    bool isCharacter(const char c);

    bool isCharacters(const char *str);

    bool isString(const char *str);
    
    // returns keyword id if str is a keyword, else returns -1
    int isKeyword(const char *str);
    
    void addToken(const int id, const char *str);

    void runKernel(const char *input);
    
public:
    TokenList run(const std::string &code);
};