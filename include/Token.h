//
// Created by Hibiki33 on 2023/6/25.
//

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#pragma once
#include <string>
#include <iostream>

namespace Front {
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
        Token();

        explicit Token(const std::string& sym, const std::string& str, int lin);

        ~Token();

        std::string getTokenSymbol() const;
        std::string getTokenString() const;
        int getTokenLineNumber() const;

    private:
        std::string tokenSymbol;
        std::string tokenString;
        int tokenLineNumber{};

    };

    std::ostream& operator<<(const std::ostream& os, Token token);
}

#endif //COMPILER_TOKEN_H
