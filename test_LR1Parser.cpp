#include "ToyFileIO/ToyFileIO.h"
#include "ToyLexer/ToyLexer.h"
#include "ToySyntaxer/ToySyntaxer.h"
#include "ToyLR1Parser/ToyLR1Parser.h"

using namespace std;

int main(void) {
    auto grammar = ToyFileIO::readFile("ToyGrammar/Toy_LR1.grammar");
    ToyLexer lexer;
    ToySyntaxer syntaxer;
    syntaxer.parseGrammar(grammar);

    // 输出 Toy_LR1.grammar 语法经 LR(1) 分析得到的
    // LR(1) 项目集规范族和 LR(1) 分析表至文件
    ToyLR1Parser parser(syntaxer);
    cout << "Running tests of canonical LR(1) collection and LR(1) table..." << endl;
    ToyFileIO::writeFile("Toy_LR1_LR1Table.csv", parser.writeLR1Table(syntaxer));
    ToyFileIO::writeFile("Toy_LR1_LR1States.txt", parser.writeLR1States());
    cout << "Success!" << endl;

    // 输出 test_01.toy 代码经 LR(1) 分析得到的语法树至文件
    cout << "Running test of LR(1) analysis on \"test_01.toy\"..." << endl;
    auto code_01 = ToyFileIO::readFile("ToyCode/test_01.toy");
    auto tokenList_01 = lexer.run(code_01);
    auto ast_01 = parser.run(tokenList_01);
    ToyFileIO::writeFile("test_01_LR1.xml", ast_01.writeToyAST());
    
    // 输出 test_02.toy 代码经 LR(1) 分析得到的语法树至文件
    cout << "Running test of LR(1) analysis on \"test_02.toy\"..." << endl;
    auto code_02 = ToyFileIO::readFile("ToyCode/test_02.toy");
    auto tokenList_02 = lexer.run(code_02);
    auto ast_02 = parser.run(tokenList_02);
    ToyFileIO::writeFile("test_02_LR1.xml", ast_02.writeToyAST());
    return 0;
}
