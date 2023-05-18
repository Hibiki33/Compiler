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

    reservedSingle["+"] = PLUS;
    reservedSingle["-"] = MINU;
    reservedSingle["*"] = MULT;
    reservedSingle["/"] = DIV;
    reservedSingle["%"] = MOD;
    reservedSingle[";"] = SEMICN;
    reservedSingle[","] = COMMA;
    reservedSingle["("] = LPARENT;
    reservedSingle[")"] = RPARENT;
    reservedSingle["["] = LBRACK;
    reservedSingle["]"] = RBRACK;
    reservedSingle["{"] = LBRACE;
    reservedSingle["}"] = RBRACE;

    reservedSpecial["&&"] = AND;
    reservedSpecial["||"] = OR;
    reservedSpecial["<"] = LSS;
    reservedSpecial["<="] = LEQ;
    reservedSpecial[">"] = GRE;
    reservedSpecial[">="] = GEQ;
    reservedSpecial["="] = ASSIGN;
    reservedSpecial["=="] = EQL;
    reservedSpecial["!"] = NOT;
    reservedSpecial["!="] = NEQ;
    reservedSpecial["\""] = STRCON;
    reservedSpecial["//"] = SLC;
    reservedSpecial["/*"] = LMLC;
    reservedSpecial["*/"] = RMLC;

    sourceFile.open(fileName);

    bufCh = (char)sourceFile.get();
}
LexicalAnalyzer::~LexicalAnalyzer() {
    sourceFile.close();
}

void LexicalAnalyzer::nextLexeme() {
    presentString.clear();

    if (sourceFile.eof()) {
        presentLexeme = FINISH;
    }

    while (std::isspace(bufCh)) {
        bufCh = (char)sourceFile.get();
    }

    if (std::isdigit(bufCh)) {
        presentLexeme = INTCON;
        for (; std::isdigit(bufCh); bufCh = (char)sourceFile.get()) {
            presentString += bufCh;
        }
    } else if (std::isalpha(bufCh)) {
        for (; std::isalpha(bufCh); bufCh = (char)sourceFile.get()) {
            presentString += bufCh;
        }

        auto iter = reservedWords.find(presentString);
        if (iter != reservedWords.end()) {
            presentLexeme = iter->second;
        } else {
            presentLexeme = IDENFR;
        }
    } else {
        presentString += bufCh;
        auto iterSingle = reservedSingle.find(presentString);
        if (iterSingle != reservedSingle.end()) {
            presentLexeme = iterSingle->second;
            bufCh = (char)sourceFile.get();
        } else {
            bufCh = (char)sourceFile.get();
            std::string tempString = presentString + bufCh;
            auto iterSpecial = reservedSpecial.find(tempString);
            if (iterSpecial != reservedSpecial.end()) {
                if (iterSpecial->second == SLC) {
                    while (bufCh != '\n') {
                        bufCh = (char)sourceFile.get();
                    }
                    bufCh = (char)sourceFile.get();
                    nextLexeme();
                } else if (iterSpecial->second == LMLC) {
                    bufCh = (char)sourceFile.get();
                    char tempCh = bufCh;
                    while (!(tempCh == '*' && bufCh == '/')) {
                        bufCh = (char)sourceFile.get();
                        tempCh = bufCh;
                    }
                    bufCh = (char)sourceFile.get();
                    nextLexeme();
                } else {
                    presentString += bufCh;
                    presentLexeme = iterSpecial->second;
                    bufCh = (char)sourceFile.get();
                }
            } else {
                iterSpecial = reservedSpecial.find(presentString);
                if (iterSpecial != reservedSpecial.end()) {
                    presentLexeme = iterSpecial->second;
                    if (presentLexeme == STRCON) {
                        while (bufCh != '\"') {
                            presentString += bufCh;
                            bufCh = (char)sourceFile.get();
                        }
                        presentString += bufCh;
                        bufCh = (char)sourceFile.get();
                    }
                    // next bufCh already exist
                } else {
                    std::cerr << "ERROR" << std::endl;
                }
            }

        }
    }
}

std::string LexicalAnalyzer::getPresentString() {
    return presentString;
}

LexemeSymbol LexicalAnalyzer::getPresentLexeme() {
    return presentLexeme;
}
