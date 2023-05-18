//
// Created by Hibiki33 on 2023/5/17.
//

#ifndef COMPILER_LEXICALANALYZER_H
#define COMPILER_LEXICALANALYZER_H

#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>

enum LexemeSymbol {
    IDENFR,     // Ident
    INTCON,     // IntConst
    STRCON,     // FormatString
    MAINTK,     // main
    CONSTTK,    // const
    INTTK,      // int
    BREAKTK,    // break
    CONTINUETK, // continue
    IFTK,       // if
    ELSETK,     // else
    NOT,        // !
    AND,        // &&
    OR,         // ||
    WHILETK,    // while
    GETINTTK,   // getint
    PRINTFTK,   // printf
    RETURNTK,   // return
    PLUS,       // +
    MINU,       // -
    VOIDTK,     // void
    MULT,       // *
    DIV,        // /
    MOD,        // %
    LSS,        // <
    LEQ,        // <=
    GRE,        // >
    GRQ,        // >=
    EQL,        // ==
    NEQ,        // !=
    ASSIGN,     // =
    SEMICN,     // ;
    COMMA,      // ,
    LPARENT,    // (
    RPARENT,    // )
    LBRACK,     // [
    RBRACK,     // ]
    LBRACE,     // {
    RBRACE,     // }

    FINISH
};

class LexicalAnalyzer {
public:
    void nextLexeme();

private:
    std::ifstream sourceFile;

    static std::map<std::string, LexemeSymbol> reservedWords;

    std::string presentString;

    LexemeSymbol presentLexeme;

    char bufCh;

    explicit LexicalAnalyzer(const std::string& fileName);

    ~LexicalAnalyzer();

    std::string getPresentString();

    LexemeSymbol getPresentLexeme();
};


#endif //COMPILER_LEXICALANALYZER_H
