//
// Created by Hibiki33 on 2023/6/25.
//

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#pragma once
#include <string>

// #define Token std::tuple<std::string, std::string, int>
//
// #define getTokenSymbol(x) std::get<0>(x)
// #define getTokenString(x) std::get<1>(x)
// #define getTokenLineNumber std::get<2>(x)
// #define makeToken(x, y, z) std::make_tuple(x, y, z)

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

class Token {
public:
    explicit Token(const std::string& sym, const std::string& str, int lin);

    ~Token();

    std::string getTokenSymbol();
    std::string getTokenString();
    int getTokenLineNumber() const;

private:
    std::string tokenSymbol;
    std::string tokenString;
    int tokenLineNumber;

};

#endif //COMPILER_TOKEN_H
