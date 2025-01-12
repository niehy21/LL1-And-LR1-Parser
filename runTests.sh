echo "Running test_FileIO..."
g++ test_FileIO.cpp ToyFileIO/ToyFileIO.cpp -o test_FileIO
./test_FileIO
echo "Running test_Lexer..."
g++ test_Lexer.cpp ToyFileIO/ToyFileIO.cpp ToyLexer/Token.cpp ToyLexer/TokenDict.cpp ToyLexer/TokenList.cpp ToyLexer/ToyLexer.cpp -o test_Lexer
./test_Lexer
echo "Running test_Syntaxer..."
g++ test_Syntaxer.cpp ToyFileIO/ToyFileIO.cpp ToySyntaxer/Symbol.cpp ToySyntaxer/ToySyntaxer.cpp -o test_Syntaxer
./test_Syntaxer
echo "Running test_LL1Parser..."
g++ test_LL1Parser.cpp ToyLexer/Token.cpp ToyLexer/TokenDict.cpp ToyLexer/TokenList.cpp ToyLexer/ToyLexer.cpp ToyFileIO/ToyFileIO.cpp ToySyntaxer/Symbol.cpp ToySyntaxer/Production.cpp ToySyntaxer/ToySyntaxer.cpp ToyAST/ToyAST.cpp ToyLL1Parser/ToyLL1Parser.cpp -o test_LL1Parser
./test_LL1Parser
echo "Running test_LR1Parser..."
g++ test_LR1Parser.cpp ToyLexer/Token.cpp ToyLexer/TokenDict.cpp ToyLexer/TokenList.cpp ToyLexer/ToyLexer.cpp ToyFileIO/ToyFileIO.cpp ToySyntaxer/Symbol.cpp ToySyntaxer/Production.cpp ToySyntaxer/ToySyntaxer.cpp ToyAST/ToyAST.cpp ToyLR1Parser/LR1Table.cpp ToyLR1Parser/ToyLR1Parser.cpp -o test_LR1Parser
./test_LR1Parser
echo "Running test_XMLCompare..."
g++ test_XMLCompare.cpp ToyFileIO/ToyFileIO.cpp -o test_XMLCompare
./test_XMLCompare

rm ./test_FileIO ./test_Lexer ./test_Syntaxer ./test_LL1Parser ./test_LR1Parser ./test_XMLCompare

read -rsn1 -p "Press any key to continue..."; echo
