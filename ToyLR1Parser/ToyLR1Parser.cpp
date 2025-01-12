#include "ToyLR1Parser.h"

#include <stack>
#include <map>
#include <queue>
#include <algorithm>

void ToyLR1Parser::getLR1States(ToySyntaxer &syntaxer) {
    // 最新状态序号
    std::size_t latest = 0;
    
    // 初始项目集 I₀
    LR1State I0;

    // 初始项目必为 S' -> .S, $
    // 接受项目必为 S' -> S., $
    LR1Item startItem(Production("S'", { syntaxer.startSymbol }), 0, "$"),
            acceptItem(Production("S'", { syntaxer.startSymbol }), 1, "$");
    I0.items.emplace(std::move(startItem));
    I0.getClosure(syntaxer);
    states.emplace_back(std::move(I0));

    // 待处理的项目集序号的队列
    std::queue<std::size_t> todos;
    todos.emplace(0);

    while (!todos.empty()) {
        auto todoIndex = todos.front();
        auto &todo = states[todoIndex];
        todos.pop();

        // LR(1) 自动机中的变迁, 代表移进或规约
        std::map<Symbol, LR1State> transitions;
        for (const auto &item : todo.items) {
            // 规约项目, A -> α., a
            if (item.dot == item.p.rhs.size()) {
                // Action 表已有对应项, 说明发生冲突
                if (table.actions.find({ item.lookahead, todoIndex }) !=
                    table.actions.end()) {
                    std::cout << "Conflict occurred in LR(1) analysis!" << std::endl;
                    exit(EXIT_FAILURE);
                }
                // 接受项目, S' -> S., $
                if (item == acceptItem) {
                    table.actions[{ item.lookahead, todoIndex }] = Action(ACCEPT, 0xffffffff);
                // 普通规约项目
                } else {
                    std::size_t index = std::find(productions.cbegin(), productions.cend(), item.p) - productions.cbegin();
                    table.actions[{ item.lookahead, todoIndex }] = Action(REDUCE, index);
                }
                continue;
            // 移进项目或待约项目, A -> α.Bβ, a 或 A -> α.bβ, a
            } else if (item.dot < item.p.rhs.size()) {
                Symbol B = item.p.rhs[item.dot];
                transitions[B].items.emplace(item.p, item.dot + 1, item.lookahead);
            // 点位置超出范围
            } else {
                std::cout << "Unknown error occurred in LR(1) analysis!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        for (auto &transition : transitions) {
            // 求闭包, 若新项目集为空, 则报错
            if (transition.second.getClosure(syntaxer).items.empty()) {
                std::cout << "Unknown error occurred in LR(1) analysis!" << std::endl;
                exit(EXIT_FAILURE);
            }

            // 若项目集未出现过, 则在项目集列表中新增一个, 并标记为待处理
            std::size_t index = std::find(states.cbegin(), states.cend(), transition.second) - states.cbegin();
            if (index == states.size()) {
                states.emplace_back(std::move(transition.second));
                todos.emplace(index);
            }

            // 变迁为终结符, 移进项目, 写 Action 表
            if (transition.first.isTerminal()) {
                // Action 表已有对应项, 说明发生冲突
                if (table.actions.find({ transition.first, todoIndex }) !=
                    table.actions.end()) {
                    std::cout << "Conflict occurred in LR(1) analysis!" << std::endl;
                    exit(EXIT_FAILURE);
                }

                table.actions[{ transition.first, todoIndex }] = Action(SHIFT, index);
            // 变迁为非终结符, 待约项目, 写 Goto 表
            } else {
                // Goto 表已有对应项, 说明发生冲突
                if (table.gotos.find({ transition.first, todoIndex }) !=
                    table.gotos.end()) {
                    std::cout << "Conflict occurred in LR(1) analysis!" << std::endl;
                    exit(EXIT_FAILURE);
                }

                table.gotos[{ transition.first, todoIndex }] = index;
            }
        }
    }
}

std::string ToyLR1Parser::writeLR1States() {
    std::string buf;
    for (int i = 0; i < states.size(); i++) {
        buf += std::to_string(i) + ":\n";
        for (const auto &item : states[i].items) {
            buf += "    " + to_string(item) + "\n";
        }
        buf += "\n";
    }
    return buf;
}

std::string ToyLR1Parser::writeLR1Table(ToySyntaxer &syntaxer) {
    std::string CSVString = "State";
    for (const auto &terminal : syntaxer.terminalSymbols) {
        CSVString += "," + terminal;
    }
    for (const auto &nonterminal : syntaxer.nonterminalSymbols) {
        CSVString += "," + nonterminal;
    }
    CSVString += "\n";
    for (int i = 0; i < states.size(); i++) {
        CSVString += std::to_string(i);
        for (const auto &terminal : syntaxer.terminalSymbols) {
            CSVString += ",";
            if (table.actions.find({ terminal, i }) != table.actions.end()) {
                const auto &action = table.actions[{ terminal, i }];
                switch (action.type) {
                    case SHIFT:
                        CSVString += "shift " + std::to_string(action.to);
                        break;
                    case REDUCE:
                        CSVString += "reduce " + to_string(productions[action.to]);
                        break;
                    case ACCEPT:
                        CSVString += "accept";
                        break;
                    default:
                        CSVString += "error";
                        break;
                }
            }
        }
        for (const auto &nonterminal : syntaxer.nonterminalSymbols) {
            CSVString += ",";
            if (table.gotos.find({ nonterminal, i }) != table.gotos.end()) {
                CSVString += std::to_string(table.gotos[{ nonterminal, i }]);
            }
        }
        CSVString += "\n";
    }
    return CSVString;
}

ToyAST ToyLR1Parser::run(const TokenList &tokenList) {
    // Augment the token list with $
    TokenList augmentedTokenList(tokenList);
    augmentedTokenList.emplace_back(0, "$", "$");

    // Stack of state sequence numbers
    std::stack<std::size_t> stateStack;
    stateStack.emplace(0);

    // Stack of ToyASTNode
    std::stack<ToyASTNode *> nodeStack;

    // Iterator of current token
    auto iterToken = augmentedTokenList.cbegin();

    while (true) {
        const auto &state = stateStack.top();
        
        if (table.actions.find({ iterToken->tag, state }) == table.actions.end()) {
            std::cout << "Action[" << state << ", " << iterToken->tag << "] = error" << std::endl;
            std::cout << "An error occurred in LR(1) analysis." << std::endl;
            exit(EXIT_FAILURE);
        }

        const auto &action = table.actions[{ iterToken->tag, state }];
        switch (action.type) {
            case SHIFT:
                stateStack.emplace(action.to);
                nodeStack.emplace(new ToyASTNode(
                    iterToken->tag,
                    iterToken->value,
                    0
                ));
                iterToken++;
                break;
            case REDUCE: {
                const auto &production = productions[action.to];
                const auto &lhs = production.lhs;
                std::size_t rhsSize = production.rhs.size();

                // Pop |β| states, and push the state of A
                for (int i = 0; i < rhsSize; i++) {
                    stateStack.pop();
                }
                std::size_t newState = table.gotos[{ lhs, stateStack.top() }];
                stateStack.emplace(newState);

                // Pop |β| nodes into a new stack (to reverse the order),
                // and add them into node A's children 
                std::stack<ToyASTNode *> poppedNodes;
                for (int i = 0; i < rhsSize; i++) {
                    poppedNodes.emplace(nodeStack.top());
                    nodeStack.pop();
                }
                auto lhsNode = new ToyASTNode(lhs, "", 0);
                for (int i = 0; i < rhsSize; i++) {
                    lhsNode->addChild(poppedNodes.top());
                    poppedNodes.pop();
                }
                nodeStack.emplace(lhsNode);
                break;
            }
            case ACCEPT:
                std::cout << "Success!" << std::endl;
                return ToyAST(nodeStack.top()).adjustDepth();
            default:
                break;
        }
    }
}
