#pragma once

#include "LR1Table.h"
#include "../ToyLexer/ToyLexer.h"
#include "../ToySyntaxer/ToySyntaxer.h"
#include "../ToyAST/ToyAST.h"

#include <string>

struct ToyLR1Parser {
    // 产生式集
    std::vector<Production> productions;
    
    // LR(1) 项目集规范族
    std::vector<LR1State> states;

    // LR(1) 分析表, 包含 Action 表和 Goto 表
    LR1Table table;

    // 在构造函数中完成 LR(1) 分析表的构造
    // 表为映射，若键不在映射中，即出错标志
    ToyLR1Parser(
        ToySyntaxer &syntaxer
    ) {
        // 将产生式填入 LR(1) 分析器
        // production: A → α1 | α2 | ...
        for (const auto production : syntaxer.productions) {
            const auto &A = production.first;
            for (const auto &alpha : production.second) {
                productions.emplace_back(A, alpha);
            }
        }
        
        // 构造 LR(1) 自动机和分析表
        getLR1States(syntaxer);
    }

    void getLR1States(ToySyntaxer &syntaxer);

    // 将 LR(1) 项目集规范族转换为字符串
    std::string writeLR1States();

    // 将 LR(1) 分析表以 CSV 格式转换为字符串
    std::string writeLR1Table(ToySyntaxer &syntaxer);
    ToyAST run(const TokenList &tokenList);
};