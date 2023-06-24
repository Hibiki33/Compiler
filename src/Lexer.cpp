//
// Created by Hibiki33 on 2023/05/17.
//

#include "Lexer.h"

Lexer::Lexer(const std::string& fileName) {
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
    reservedSpecial["*"] = MULT;
    reservedSpecial["/"] = DIV;
    reservedSpecial["//"] = SLC;
    reservedSpecial["/*"] = LMLC;
    reservedSpecial["*/"] = RMLC;

    sourceFile.open(fileName);

    bufCh = (char)sourceFile.get();

    presentString = "";
    presentLexeme = BEGIN;
}

Lexer::~Lexer() {
    sourceFile.close();
}

/*
 * Overview: Get next valid lexeme.
 *  Set next lexeme's symbol to 'presentLexeme'.
 *  Set next lexeme itself to 'presentString'.
 */
void Lexer::nextLexeme() {
    presentString.clear();

    // ignore invalid characters
    while (std::isspace(bufCh) || bufCh == '\n' || bufCh == '\r') {
        bufCh = (char)sourceFile.get();
    }

    if (sourceFile.eof()) {
        presentLexeme = END;
        return;
    }

    if (std::isdigit(bufCh)) {
        // parse numeric constants
        presentLexeme = INTCON;
        for (; std::isdigit(bufCh); bufCh = (char)sourceFile.get()) {
            presentString += bufCh;
        }
    } else if (std::isalpha(bufCh) || bufCh == '_') {
        // parse identifier variables or reserved words
        for (; std::isalpha(bufCh) || bufCh == '_' || std::isdigit(bufCh); bufCh = (char)sourceFile.get()) {
            presentString += bufCh;
        }
        auto iter = reservedWords.find(presentString);
        if (iter != reservedWords.end()) {
            presentLexeme = iter->second;
        } else {
            presentLexeme = IDENFR;
        }
    } else {
        // parse reserved symbols
        presentString += bufCh;
        auto iterSingle = reservedSingle.find(presentString);
        if (iterSingle != reservedSingle.end()) {
            // definitely single symbols
            presentLexeme = iterSingle->second;
            bufCh = (char)sourceFile.get();
        } else {
            // possibly single symbols or double symbols
            bufCh = (char)sourceFile.get();
            std::string tempString = presentString + bufCh;
            auto iterSpecial = reservedSpecial.find(tempString);
            if (iterSpecial != reservedSpecial.end()) {
                // double symbols or comments
                if (iterSpecial->second == SLC) {
                    // specially handle comments
                    // recursively invoke 'nextLexeme' to get the next valid lexeme
                    while (!sourceFile.eof() && bufCh != '\n' && bufCh != '\r') {
                        bufCh = (char)sourceFile.get();
                    }
                    bufCh = (char)sourceFile.get();
                    nextLexeme();
                } else if (iterSpecial->second == LMLC) {
                    // specially handle comments
                    // recursively invoke 'nextLexeme' to get the next valid lexeme
                    bufCh = (char)sourceFile.get();
                    char tempCh = bufCh;
                    bufCh = (char)sourceFile.get();
                    while (!(tempCh == '*' && bufCh == '/')) {
                        tempCh = bufCh;
                        bufCh = (char)sourceFile.get();
                    }
                    bufCh = (char)sourceFile.get();
                    nextLexeme();
                } else {
                    // double symbols
                    presentString += bufCh;
                    presentLexeme = iterSpecial->second;
                    bufCh = (char)sourceFile.get();
                }
            } else {
                iterSpecial = reservedSpecial.find(presentString);
                if (iterSpecial != reservedSpecial.end()) {
                    presentLexeme = iterSpecial->second;
                    if (presentLexeme == STRCON) {
                        // specially handle comments
                        while (bufCh != '\"') {
                            presentString += bufCh;
                            bufCh = (char)sourceFile.get();
                        }
                        presentString += bufCh;
                        bufCh = (char)sourceFile.get();
                    }
                    // nothing else to do for special single symbols
                } else {
                    std::cerr << "ERROR" << std::endl;
                }
            }
        }
    }
}

/*
 * Overview: Get present lexeme.
 */
std::string Lexer::getPresentString() {
    return presentString;
}

/*
 * Overview: Get present lexeme's symbol.
 */
LexemeSymbol Lexer::getPresentLexeme() {
    return presentLexeme;
}
