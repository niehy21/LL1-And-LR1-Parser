// C++ program to illustrate the implementation of lexical analyser

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "ToyLexer.h"

// str[start:end]
static char *slice(char dest[], int destVolume, const char *src, int start, int end) {
    int srcLength  = strlen(src);
    int destLength = end - start;
    strncpy(dest, src + start, destLength);
    dest[destVolume - 1 <= destLength ? destVolume - 1 : destLength] = '\0';
    return dest;
}

bool ToyLexer::isDelimiter(const char c) {
    return (isblank(c) || c == '\n' || c == '\r' || isTaggedDelimiter(c));
}

bool ToyLexer::isIdentifierRest(const char *str) {
    return str[0] ? (isalnum(str[0]) && isIdentifierRest(str + 1)) : true;
}

bool ToyLexer::isIdentifier(const char *str) {
    return isalpha(str[0]) && isIdentifierRest(str + 1);
}

bool ToyLexer::isNumberRest(const char *str) {
    return str[0] ? (isdigit(str[0]) && isNumberRest(str + 1)) : true;
}

bool ToyLexer::isNumber(const char *str) {
    int length = strlen(str);
    return (length && isdigit(str[0]) && isNumberRest(str + 1)) ||
        (length > 1 && str[0] == '-' && isdigit(str[1]) && isNumberRest(str + 2));
}

bool ToyLexer::isCharacter(const char c) {
    return isalnum(c) || (ispunct(c) && (c != 34)) || (c == 32);
}

bool ToyLexer::isCharacters(const char *str) {
    return str[0] ? isCharacter(str[0]) && isCharacters(str + 1) : true;
}

bool ToyLexer::isString(const char *str) {
    int length = strlen(str);
    std::string str_t(str + 1, length - 2);
    return str[0] == 34 && str[length - 1] == 34 && isCharacters(str_t.c_str());
}

int ToyLexer::isKeyword(const char *str) {
    for (int i = 0; i < keywordList.size(); i++) {
        if (strcmp(str, keywordList[i].c_str()) == 0) {
            return i;
        }
    }
    return -1;
}

void ToyLexer::addToken(const int id, const char *str) {
    tokenList.emplace_back(id, tokenDict[id], Token::TokenValue(str));
}

// this function parse the input
void ToyLexer::runKernel(const char *input) {
    int left = 0, right = 0, id = -1;
    int len = strlen(input);
    const int MAX_LENGTH = 1024;
    char tmp[1024];
    tokenList.clear();
    while (right <= len && left <= right) {
        if (!isDelimiter(input[right])) {
            right++;
        }
        if (isDelimiter(input[right]) && left == right) {
            if (isTaggedDelimiter(input[right])) {
                if (input[left] == '-' && isdigit(input[left + 1])) {
                    while (isdigit(input[right + 1])) {
                        right++;
                    }
                    addToken(NUMBER, slice(tmp, MAX_LENGTH, input, left, right + 1));
                } else if (input[left] == '=' && input[right + 1] == '=') {
                    addToken(EQUAL, slice(tmp, MAX_LENGTH, input, left, ++right + 1));
                } else {
                    addToken(input[right], slice(tmp, MAX_LENGTH, input, left, right + 1));
                }
            }
            left = ++right;
        }
        else if (isDelimiter(input[right]) && left != right || (right == len && left != right)) {
            slice(tmp, MAX_LENGTH, input, left, right);
            if ((id = isKeyword(tmp)) != -1)
                tokenList.emplace_back(IDENTIFIER, tmp, tmp);
                // printf("('%s', '%s')\n", tmp, tmp);
            else if (isNumber(tmp))
                addToken(NUMBER, tmp);
                // printToken(NUMBER, tmp);
            else if (isIdentifier(tmp) && !isDelimiter(input[right - 1]))
                addToken(IDENTIFIER, tmp);
                // printToken(IDENTIFIER, tmp);
            else if (!isIdentifier(tmp) && !isDelimiter(input[right - 1])) {
                // detect string literals
                if (tmp[0] == 34) {
                    if (right == left + 1) {
                        right++;
                    }
                    while (input[right - 1] && input[right - 1] != 34) {
                        right++;
                    }
                    char *str = (char *)malloc(sizeof(char) * (right - left + 1));
                    strncpy(str, input + left, right - left);
                    str[right - left] = '\0';
                    if (input[right - 1]) {
                        addToken(STRING_LITERAL, str);
                        // printToken(STRING_LITERAL, str);
                    } else {
                        addToken(UNIDENTIFIED, str);
                        // printf("('unidentified', '%s')\n", str);
                    }
                    free(str);
                } else {
                    addToken(UNIDENTIFIED, tmp);
                    // printf("('unidentified', '%s')\n", tmp);
                }
            }
            left = right;
        }
    }
}

TokenList ToyLexer::run(const std::string &code) {
    runKernel(code.c_str());
    for (auto iter = tokenList.begin(); iter != tokenList.end();) {
        if (iter->tag == "unidentified" && iter->value == "") {
            iter = tokenList.erase(iter);
        } else {
            iter++;
        }
    }
    return tokenList;
}

// int main(int argc, char **argv) {
//     FILE *fp = (void *)0;
//     char *code;
//     long codeLength = 0;
//     int result = 0;
    
//     // detect the arguments
//     if (argc != 2) {
//         printf("Usage: ./lexer.exe <YOUR TOY SOURCE FILE PATH HERE>");
//         return 0;
//     } else {
//         char c;
//         int index = 0;
//         fp = fopen(argv[1], "r");
//         if (!fp) {
//             printf("An error occurred when opening file \"%s\"", argv[1]);
//             return 0;
//         }
//         code = fileToString(fp);
//         // printf("%d\n", index);
//         fclose(fp);
//         fp = (void *)0;
//         // printf("%s\n", code);
//     }

//     // Initialize the dict
//     initializeDict();

//     // Lexical analysis
//     TokenList *pList = lexer(code);
//     printTokenList(pList);
//     freeTokenList(pList);

//     if (code) {
//         free(code);
//     }
//     return 0;
// }