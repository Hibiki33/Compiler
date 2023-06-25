//
// Created by Hibiki33 on 2023/5/17.
//

#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "Token.h"

class Lexer {
public:
    void nextToken();

    explicit Lexer(const std::string& fileName);

    ~Lexer();

    std::string getPresentString();
    TokenSymbol getPresentToken();
    int getPresentLineNumber() const;

    std::vector<Token> tokenList;
    Token getToken(int index);

private:
    std::ifstream sourceFile;

    std::map<std::string, TokenSymbol> reservedWords;
    std::map<std::string, TokenSymbol> reservedSingle;
    std::map<std::string, TokenSymbol> reservedSpecial;

    std::string presentString;
    TokenSymbol presentToken;
    int presentLineNumber;

    void addToken(TokenSymbol sym, const std::string& str, int lin);

    char bufCh;
};

#endif //COMPILER_LEXER_H
