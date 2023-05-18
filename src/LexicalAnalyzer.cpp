//
// Created by Hibiki33 on 2023/05/17.
//

#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(const std::string& fileName) {
    reservedWords["main"] = MAINTK;
    reservedWords["const"] = CONSTTK;
    reservedWords["int"] = INTTK;
    reservedWords["break"] = BREAKTK;
    reservedWords["continue"] = CONTINUETK;
    reservedWords["if"] = IFTK;
    reservedWords["else"] = ELSETK;
    reservedWords["while"] = WHILETK;
    reservedWords["getint"] = GETINTTK;
    reservedWords["printf"] = PRINTFTK;
    reservedWords["return"] = RETURNTK;
    reservedWords["void"] = VOIDTK;

    sourceFile.open(fileName);

    bufCh = (char)sourceFile.get();
}
LexicalAnalyzer::~LexicalAnalyzer() {
    sourceFile.close();
}

void LexicalAnalyzer::nextLexeme() {
    presentString.clear();

    while (std::isspace(bufCh)) {
        bufCh = (char)sourceFile.get();
    }

    if (std::isdigit(bufCh)) {
        presentLexeme = INTCON;
        presentString += bufCh;
        for (bufCh = (char)sourceFile.get(); std::isdigit(bufCh); bufCh = (char)sourceFile.get()) {
            presentString += bufCh;
        }
    } else if (std::isalpha(bufCh)) {
        presentString += bufCh;
        for (bufCh = (char)sourceFile.get(); std::isalpha(bufCh); bufCh = (char)sourceFile.get()) {
            presentString += bufCh;
        }

        auto it = reservedWords.find(presentString);
        if (it != reservedWords.end()) {
            presentLexeme = it->second;
        } else {
            presentLexeme = IDENFR;
        }
    } else {
        presentString += bufCh;
        switch (bufCh) {
            case '!':
                presentLexeme = NOT;
                break;
            case '&':
                bufCh = (char)sourceFile.get();

        }

    }

}

std::string LexicalAnalyzer::getPresentString() {
    return presentString;
}

LexemeSymbol LexicalAnalyzer::getPresentLexeme() {
    return presentLexeme;
}
