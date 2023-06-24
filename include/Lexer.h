//
// Created by Hibiki33 on 2023/5/17.
//

#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

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

const std::string lexemeSymbolNames[] {
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

class Lexer {
public:
    void nextLexeme();

    explicit Lexer(const std::string& fileName);

    ~Lexer();

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


#endif //COMPILER_LEXER_H
