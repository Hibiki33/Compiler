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
    explicit Lexer(const std::string& fileName);

    ~Lexer();

    void nextToken();

    TokenSymbol getPresentToken();
    std::string getPresentString();
    int getPresentLineNumber() const;

    Token getToken(int index);
    std::vector<Token> getTokenList();

private:
    std::ifstream sourceFile;

    std::map<std::string, TokenSymbol> reservedWords;
    std::map<std::string, TokenSymbol> reservedSingle;
    std::map<std::string, TokenSymbol> reservedSpecial;

    TokenSymbol presentToken;
    std::string presentString;
    int presentLineNumber;

    std::vector<Token> tokenList;
    void addToken(TokenSymbol sym, const std::string& str, int lin);

    char bufCh;
};

#endif //COMPILER_LEXER_H
