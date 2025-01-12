#include "ToyFileIO/ToyFileIO.h"
#include "ToyLL1Parser/ToyLL1Parser.h"

using namespace std;

int main(void) {
    auto grammar = ToyFileIO::readFile("ToyGrammar/Toy_LL1.grammar");
    ToyLexer lexer;
    ToySyntaxer syntaxer;
    syntaxer.parseGrammar(grammar);

    // 输出 Toy_LL1.grammar 语法经 LL(1) 分析得到的
    // LL(1) 分析表至文件
    cout << "Running test of LR(1) table..." << endl;
    ToyLL1Parser parser(syntaxer);
    ToyFileIO::writeFile("Toy_LL1_LL1Table.csv", parser.writeLL1Table(syntaxer));
    cout << "Success!" << endl;

    // 输出 test_01.toy 代码经 LL(1) 分析得到的语法树至文件
    cout << "Running test of LL(1) analysis on \"test_01.toy\"..." << endl;
    auto code_01 = ToyFileIO::readFile("ToyCode/test_01.toy");
    auto tokenList_01 = lexer.run(code_01);
    auto ast_01 = parser.run(tokenList_01);
    ToyFileIO::writeFile("test_01_LL1.xml", ast_01.writeToyAST());
    
    // 输出 test_02.toy 代码经 LL(1) 分析得到的语法树至文件
    cout << "Running test of LL(1) analysis on \"test_02.toy\"..." << endl;
    auto code_02 = ToyFileIO::readFile("ToyCode/test_02.toy");
    auto tokenList_02 = lexer.run(code_02);
    auto ast_02 = parser.run(tokenList_02);
    ToyFileIO::writeFile("test_02_LL1.xml", ast_02.writeToyAST());
    return 0;
}
