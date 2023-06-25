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

    presentLineNumber = 1;
    presentString = "";
    presentToken = BEGIN;
}

Lexer::~Lexer() {
    sourceFile.close();
}

/*
 * Overview: Get next valid token.
 *  Set next token's symbol to 'presentToken'.
 *  Set next token itself to 'presentString'.
 */
void Lexer::nextToken() {
    presentString.clear();

    // ignore invalid characters
    while (std::isspace(bufCh) || bufCh == '\n' || bufCh == '\r') {
        // record line number
        if (bufCh == '\n') {
            presentLineNumber++;
        }
        bufCh = (char)sourceFile.get();
    }

    if (sourceFile.eof()) {
        presentToken = END;
        return;
    }

    if (std::isdigit(bufCh)) {
        // parse numeric constants
        presentToken = INTCON;
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
            presentToken = iter->second;
        } else {
            presentToken = IDENFR;
        }

    } else {
        // parse reserved symbols
        presentString += bufCh;

        auto iterSingle = reservedSingle.find(presentString);
        if (iterSingle != reservedSingle.end()) {
            // definitely single symbols
            presentToken = iterSingle->second;
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
                    // recursively invoke 'nextToken' to get the next valid token
                    while (!sourceFile.eof() && bufCh != '\n' && bufCh != '\r') {
                        bufCh = (char)sourceFile.get();
                    }
                    presentLineNumber++;
                    bufCh = (char)sourceFile.get();
                    nextToken();

                } else if (iterSpecial->second == LMLC) {
                    // specially handle comments
                    // recursively invoke 'nextToken' to get the next valid token
                    char tempCh = (char)sourceFile.get();
                    bufCh = (char)sourceFile.get();
                    while (!(tempCh == '*' && bufCh == '/') && bufCh != EOF) {
                        // record line number
                        if (bufCh == '\n') {
                            presentLineNumber++;
                        }
                        tempCh = bufCh;
                        bufCh = (char)sourceFile.get();
                    }

                    if (bufCh == EOF) {
                        std::cerr << "WITHOUT MATCHING RMLC" << std::endl;
                    }

                    bufCh = (char)sourceFile.get();
                    nextToken();

                } else {
                    // double symbols
                    presentString += bufCh;
                    presentToken = iterSpecial->second;
                    bufCh = (char)sourceFile.get();

                }
            } else {
                iterSpecial = reservedSpecial.find(presentString);
                if (iterSpecial != reservedSpecial.end()) {
                    presentToken = iterSpecial->second;
                    if (presentToken == STRCON) {
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
                    std::cerr << "INVALID TOKEN" << std::endl;

                }
            }
        }
    }

    addToken(presentToken, presentString, presentLineNumber);
}

/*
 * Overview: Get present token.
 */
std::string Lexer::getPresentString() {
    return presentString;
}

/*
 * Overview: Get present token's symbol.
 */
TokenSymbol Lexer::getPresentToken() {
    return presentToken;
}

/*
 * Overview: Get token's line number.
 */
int Lexer::getPresentLineNumber() const {
    return presentLineNumber;
}

/*
 * Overview: Add new token to 'tokenList'.
 */
void Lexer::addToken(TokenSymbol sym, const std::string& str, int lin) {
    auto token = Token(tokenSymbolNames[sym], str, lin);
    tokenList.push_back(token);
}

/*
 * Overview: Get a token from 'tokenList' with 'index'.
 */
Token Lexer::getToken(int index) {
    return tokenList[index];
}

/*
 * Overview: Get 'tokenList'.
 */
std::vector<Token> Lexer::getTokenList() {
    return tokenList;
}
