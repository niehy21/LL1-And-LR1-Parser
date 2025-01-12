#include "ToyLL1Parser.h"
// #include "../ToyLexer/ToyLexer.h"

ToyAST ToyLL1Parser::run(const TokenList &tokenList) {
    // 抽象语法树，根节点为 S'
    ToyAST ast;
    std::stack<Symbol> symbolStack;
    std::queue<Token> tokenQueue;
    std::stack<ToyASTNode *> nodeStack;
    nodeStack.emplace(nullptr);
    nodeStack.emplace(ast.pRoot);

    // Token 流的 FIFO 队列
    for (const auto &token : tokenList) {
        tokenQueue.emplace(token);
    }
    tokenQueue.emplace(Token(0, "#", "#"));

    // Symbol 流的 LIFO 栈
    symbolStack.emplace("#");
    symbolStack.emplace("S'");
    
    KeywordList keywords;
    bool flag = true;
    while (flag) {
        auto X = symbolStack.top();
        auto XNode = nodeStack.top();
        symbolStack.pop();
        nodeStack.pop();
        if (X.isTerminal() && X != "#") {
            if (X == tokenQueue.front().tag) {
                XNode->pToken->value = tokenQueue.front().value;
                tokenQueue.pop();
            } else {
                std::cout << "An error occurred in LL(1) analysis." << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (X == "#") {
            if (tokenQueue.front().tag == "#") {
                flag = false;
            } else {
                std::cout << "An error occurred in LL(1) analysis." << std::endl;
                exit(EXIT_FAILURE);
            }
        } else {
            std::string t = (tokenQueue.front().tag == "#") ? "$" : tokenQueue.front().tag;
            if (table.find({ X, t }) != table.end()) {
                auto production = table[{ X, t }];
                auto iter = production.rhs.end() - 1;
                // std::cout << production << std::endl;
                if (*iter == "$") {
                    continue;
                }
                do {
                    // std::cout << *iter << std::endl;
                    symbolStack.emplace(*iter);
                    nodeStack.emplace(XNode->addChild(*iter, ""));
                } while (iter-- != production.rhs.begin());
                
            } else {
                std::cout << "M[" << X << ", " << t << "] = error" << std::endl;
                std::cout << "An error occurred in LL(1) analysis." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    // 由于得到的树左右正好是颠倒的, 需要翻转链表
    ast.pRoot->inverseChildren();

    // 去除 S' 标签
    auto newRoot = ast.pRoot->pFirstChild;
    ast.pRoot->pFirstChild = nullptr;
    delete ast.pRoot;
    ast.pRoot = newRoot;

    // 调整所有节点的高度
    ast.adjustDepth();

    std::cout << "Success!" << std::endl;
    return ast;
}

std::string ToyLL1Parser::writeLL1Table(const ToySyntaxer &syntaxer) {
    std::string CSVString = "";
    for (const auto &terminal : syntaxer.terminalSymbols) {
        CSVString += "," + terminal;
    }
    CSVString += "\n";
    for (const auto &nonterminal : syntaxer.nonterminalSymbols) {
        CSVString += nonterminal;
        for (const auto &terminal : syntaxer.terminalSymbols) {
            CSVString += ",";
            if (table.find({ nonterminal, terminal }) != table.end()) {
                CSVString += to_string(table[{ nonterminal, terminal }]);
            }
        }
        CSVString += "\n";
    }
    return CSVString;
}
