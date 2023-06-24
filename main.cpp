#include <iostream>
#include "Lexer.h"

int main() {
    std::string testFileName = "./testfiles/LexicalAnalyze/testfile.txt";
    std::string outFileName = "./testfiles/LexicalAnalyze/output.txt";

    Lexer lexicalAnalyzer(testFileName);
    std::ofstream outFile(outFileName);

    while (lexicalAnalyzer.getPresentToken() != END) {
        lexicalAnalyzer.nextToken();
        if (lexicalAnalyzer.getPresentToken() != END) {
            outFile << tokenSymbolNames[lexicalAnalyzer.getPresentToken()];
            outFile << " " << lexicalAnalyzer.getPresentString() << std::endl;
        }
    }


    return 0;
}
