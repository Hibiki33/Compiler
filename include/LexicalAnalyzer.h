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
#include <cstdlib>
#include <vector>
#include <fstream>
#include <map>

enum LexemeSymbol {
    BEGIN,

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
    GEQ,        // >=
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

    SLC,        // //
    LMLC,       // /*
    RMLC,       // */

    END
};

const std::string LexemeSymbolNames[] {
        "",             // BEGIN

        "IDENFR",       // Ident
        "INTCON",       // IntConst
        "STRCON",       // FormatString
        "MAINTK",       // main
        "CONSTTK",      // const
        "INTTK",        // int
        "BREAKTK",      // break
        "CONTINUETK",   // continue
        "IFTK",         // if
        "ELSETK",       // else
        "NOT",          // !
        "AND",          // &&
        "OR",           // ||
        "WHILETK",      // while
        "GETINTTK",     // getint
        "PRINTFTK",     // printf
        "RETURNTK",     // return
        "PLUS",         // +
        "MINU",         // -
        "VOIDTK",       // void
        "MULT",         // *
        "DIV",          // /
        "MOD",          // %
        "LSS",          // <
        "LEQ",          // <=
        "GRE",          // >
        "GEQ",          // >=
        "EQL",          // ==
        "NEQ",          // !=
        "ASSIGN",       // =
        "SEMICN",       // ;
        "COMMA",        // ,
        "LPARENT",      // (
        "RPARENT",      // )
        "LBRACK",       // [
        "RBRACK",       // ]
        "LBRACE",       // {
        "RBRACE",       // }

        "",             // //
        "",             // /*
        "",             // */

        ""              // END
};

class LexicalAnalyzer {
public:
    void nextLexeme();

    explicit LexicalAnalyzer(const std::string& fileName);

    ~LexicalAnalyzer();

    std::string getPresentString();

    LexemeSymbol getPresentLexeme();

private:
    std::ifstream sourceFile;

    std::map<std::string, LexemeSymbol> reservedWords;
    std::map<std::string, LexemeSymbol> reservedSingle;
    std::map<std::string, LexemeSymbol> reservedSpecial;

    std::string presentString;

    LexemeSymbol presentLexeme;

    char bufCh;
};


#endif //COMPILER_LEXICALANALYZER_H
