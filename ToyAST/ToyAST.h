#pragma once

#include "../ToyLexer/ToyLexer.h"
#include <string>

struct ToyASTNode {
    Token *pToken = nullptr;
    ToyASTNode *pFirstChild = nullptr, *pNextSibling = nullptr;
    int depth;

    ToyASTNode(
        const Token::TokenTag &_tag,
        const Token::TokenValue &_value,
        const int _depth,
        ToyASTNode *_pFirstChild = nullptr,
        ToyASTNode *_pNextSibling = nullptr
    ) : 
        pToken(new Token(0, _tag, _value)),
        depth(_depth),
        pFirstChild(_pFirstChild),
        pNextSibling(_pNextSibling) {
    }

    ~ToyASTNode() {
        if (pFirstChild) {
            delete pFirstChild;
        }
        if (pNextSibling) {
            delete pNextSibling;
        }
        if (pToken) {
            delete pToken;
        }
    }

    ToyASTNode *addSibling(
        ToyASTNode *createdNode
    );

    ToyASTNode *addSibling(
        const Token::TokenTag &_tag,
        const Token::TokenValue &_value
    );

    ToyASTNode *addSibling(
        const Token &_token
    );

    ToyASTNode *addChild(
        ToyASTNode *createdNode
    );

    ToyASTNode *addChild(
        const Token::TokenTag &_tag,
        const Token::TokenValue &_value
    );

    ToyASTNode *addChild(
        const Token &_token
    );

    void inverseChildren();
    void adjustDepth(const int _depth);
};

class ToyAST {
private:
    std::string XMLString;
    void writeBlanks(const int number);
    void writeToyASTNode(const ToyASTNode *pNode);
public:
    ToyASTNode *pRoot;

    ToyAST() : pRoot(new ToyASTNode("S'", "", 0)), XMLString("") {
    }

    ToyAST(ToyASTNode *_pRoot) : pRoot(_pRoot), XMLString("") {
    }

    // 将树转换为 XML 格式的字符串
    std::string &writeToyAST();

    ToyAST &adjustDepth();
};


// create a new token struct.
// when id < 0, the token is actually useless,
// value is copied to the token's tag.
// (e.g., "STATEMENT", "EXPRESSION", ...)
// ToyASTNode *createASTNodeWithData(const int id, const char *value);
// directly use the token struct.
// ToyASTNode *createASTNodeWithToken(Token *pToken);
// ToyAST *createAST();