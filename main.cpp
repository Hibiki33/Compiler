#include <iostream>
#include "Lexer.h"

int main() {
    std::string testFileName = "./testfiles/LexicalAnalyze/testfile.txt";
    std::string outFileName = "./testfiles/LexicalAnalyze/output.txt";

    Lexer lexicalAnalyzer(testFileName);
    std::ofstream outFile(outFileName);

    while (lexicalAnalyzer.getPresentLexeme() != END) {
        lexicalAnalyzer.nextLexeme();
        if (lexicalAnalyzer.getPresentLexeme() != END) {
            outFile << lexemeSymbolNames[lexicalAnalyzer.getPresentLexeme()];
            outFile << " " << lexicalAnalyzer.getPresentString() << std::endl;
        }
    }


    return 0;
}
