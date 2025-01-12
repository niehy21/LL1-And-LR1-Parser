#include "ToyAST.h"
#include "../ToySyntaxer/Symbol.h"
void ToyAST::writeBlanks(const int number) {
    for (int i = 0; i < number; i++) {
        XMLString += " ";
    }
}

void ToyAST::writeToyASTNode(const ToyASTNode *pNode) {
    Token *pToken;
    if (pNode) {
        // 空的非终结符节点直接跳过
        if (!pNode->pFirstChild && !Symbol(pNode->pToken->tag).isTerminal()) {
            return;
        }

        // 打印自身
        pToken = pNode->pToken;
        writeBlanks(pNode->depth << 2);
        XMLString += '<' + pToken->tag + '>';

        // 打印长子
        if (pNode->pFirstChild) {
            XMLString += '\n';
            writeToyASTNode(pNode->pFirstChild);
            writeBlanks(pNode->depth << 2);
        } else if (pToken->value != "") {
            if (pToken->value == ">") {
                XMLString += "&gt;";
            } else if (pToken->value == "<") {
                XMLString += "&lt;";
            } else {
                XMLString += pToken->value;
            }
        }
        XMLString += "</" + pToken->tag + ">\n";

        // 打印兄弟
        if (pNode->pNextSibling) {
            writeToyASTNode(pNode->pNextSibling);
        }
    }
}

std::string &ToyAST::writeToyAST() {
    XMLString = "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n";
    writeToyASTNode(pRoot);
    return XMLString;
}

ToyAST &ToyAST::adjustDepth() {
    pRoot->adjustDepth(0);
    return *this;
}

ToyASTNode *ToyASTNode::addSibling(
    ToyASTNode *createdNode
) {
    ToyASTNode *p = this;
    while (p->pNextSibling) {
        p = p->pNextSibling;
    }
    p->pNextSibling = createdNode;
    createdNode->depth = depth;
    return p->pNextSibling;
}

ToyASTNode *ToyASTNode::addSibling(
    const Token::TokenTag &_tag,
    const Token::TokenValue &_value
) {
    return addSibling(new ToyASTNode(_tag, _value, depth));
}

ToyASTNode *ToyASTNode::addSibling(const Token &_token) {
    return addSibling(_token.tag, _token.value);
}

ToyASTNode *ToyASTNode::addChild(
    ToyASTNode *createdNode
) {
    if (pFirstChild) {
        return pFirstChild->addSibling(createdNode);
    } else {
        pFirstChild = createdNode;
        pFirstChild->depth = depth + 1;
        return pFirstChild;
    }
}

ToyASTNode *ToyASTNode::addChild(
    const Token::TokenTag &_tag,
    const Token::TokenValue &_value
) {
    if (pFirstChild) {
        return pFirstChild->addSibling(_tag, _value);
    } else {
        pFirstChild = new ToyASTNode(_tag, _value, depth + 1);
        return pFirstChild;
    }
}

ToyASTNode *ToyASTNode::addChild(const Token &_token) {
    return addChild(_token.tag, _token.value);
}

void ToyASTNode::inverseChildren() {
    if (!pFirstChild) {
        return;
    }
    
    ToyASTNode *p = nullptr,
               *q = pFirstChild,
               *r = pFirstChild->pNextSibling;
    

    // A -> B -> C -> nil
    // p = nil, q = A, r = B

    // nil <- A  B -> C -> nil
    // p = A, q = B, r = C

    // nil <- A <- B  C -> nil
    // p = B, q = C, r = nil

    // nil <- A <- B <- C  nil
    // p = C, q = nil
    while (q) {
        q->pNextSibling = p;
        p = q;
        q = r;
        r = r ? r->pNextSibling : nullptr;
    }

    this->pFirstChild = p;

    while (p) {
        p->inverseChildren();
        p = p->pNextSibling;
    }
}

void ToyASTNode::adjustDepth(const int _depth) {
    depth = _depth;
    for (ToyASTNode *pChild = pFirstChild; pChild; pChild = pChild->pNextSibling) {
        pChild->adjustDepth(_depth + 1);
    }
}
