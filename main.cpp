#include <iostream>
#include "LexicalAnalyzer.h"

int main() {
    std::string testFileName = "./testfiles/LexicalAnalyze/testfile.txt";
    std::string outFileName = "./testfiles/LexicalAnalyze/output.txt";

    LexicalAnalyzer lexicalAnalyzer(testFileName);
    std::ofstream outFile(outFileName);

    while (lexicalAnalyzer.getPresentLexeme() != END) {
        lexicalAnalyzer.nextLexeme();
        outFile << LexemeSymbolNames[lexicalAnalyzer.getPresentLexeme()];
        outFile << " " << lexicalAnalyzer.getPresentString() << std::endl;
    }


    return 0;
}
