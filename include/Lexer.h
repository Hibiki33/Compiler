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

enum TokenSymbol {
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

const std::string tokenSymbolNames[] {
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
    void nextToken();

    explicit Lexer(const std::string& fileName);

    ~Lexer();

    std::string getPresentString();

    TokenSymbol getPresentToken();

    int getPresentLineNumber();

private:
    std::ifstream sourceFile;

    std::map<std::string, TokenSymbol> reservedWords;
    std::map<std::string, TokenSymbol> reservedSingle;
    std::map<std::string, TokenSymbol> reservedSpecial;

    std::string presentString;

    TokenSymbol presentToken;

    int presentLineNumber;

    char bufCh;
};


#endif //COMPILER_LEXER_H
