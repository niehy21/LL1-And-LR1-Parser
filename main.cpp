#include "ToyFileIO/ToyFileIO.h"
#include "ToyLexer/ToyLexer.h"
#include "ToySyntaxer/ToySyntaxer.h"
#include "ToyLR1Parser/ToyLR1Parser.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "Usage: ./parser XXX.grammar YYY.toy";
        exit(EXIT_FAILURE);
    }
    string grammarPath(argv[1]), sourcePath(argv[2]);
    if (grammarPath.substr(grammarPath.size() - 8, 8) != ".grammar" ||
        sourcePath.substr(sourcePath.size() - 4, 4) != ".toy") {
        cout << "Usage: ./parser XXX.grammar YYY.toy";
        exit(EXIT_FAILURE);
    }

    string grammarName = grammarPath.substr(0, grammarPath.size() - 8);
    string sourceName = sourcePath.substr(0, sourcePath.size() - 4);

    auto grammar = ToyFileIO::readFile(grammarPath);
    ToyLexer lexer;
    ToySyntaxer syntaxer;
    syntaxer.parseGrammar(grammar);

    // 输出语法经 LR(1) 分析得到的
    // LR(1) 项目集规范族和 LR(1) 分析表至文件
    ToyLR1Parser parser(syntaxer);
    cout << "Running tests of canonical LR(1) collection and LR(1) table..." << endl;
    ToyFileIO::writeFile(grammarName + "_LR1Table.csv", parser.writeLR1Table(syntaxer));
    ToyFileIO::writeFile(grammarName + "_LR1States.txt", parser.writeLR1States());
    cout << "Success!" << endl;

    // 输出代码经 LR(1) 分析得到的语法树至文件
    auto code = ToyFileIO::readFile(sourcePath);
    auto tokenList = lexer.run(code);
    auto ast = parser.run(tokenList);
    ToyFileIO::writeFile(sourceName + "_LR1.xml", ast.writeToyAST());
    return 0;
}
