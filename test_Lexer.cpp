#include "ToyFileIO/ToyFileIO.h"
#include "ToyLexer/ToyLexer.h"

using namespace std;

int main(void) {
    ToyLexer lexer;
    
    // 输出 test_01.toy 代码经词法分析得到的 Token 流至文件
    cout << "Running test of lexical analysis on \"test_01.toy\"..." << endl;
    std::string code_1 = ToyFileIO::readFile("ToyCode/test_01.toy");
    TokenList tokens_1 = lexer.run(code_1);
    ToyFileIO::writeFile("test_01.tokens", to_string(tokens_1));
    cout << "Success!" << endl;

    // 输出 test_02.toy 代码经词法分析得到的 Token 流至文件
    cout << "Running test of lexical analysis on \"test_02.toy\"..." << endl;
    std::string code_2 = ToyFileIO::readFile("ToyCode/test_02.toy");
    TokenList tokens_2 = lexer.run(code_2);
    ToyFileIO::writeFile("test_02.tokens", to_string(tokens_2));
    cout << "Success!" << endl;
    return 0;
}