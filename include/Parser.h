//
// Created by Hibiki33 on 2023/6/24.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "Ast.h"

namespace Front {
    class Parser {
    public:
        explicit Parser(const std::vector<Token> &tokens);

        ~Parser();

        bool syntacticAnalyze();

    private:
        std::vector<Token> tokens;

        int index;

        Ast entry;

        CompUnit parseCompUnit();
        Decl parseDecl();
        ConstDecl parseConstDecl();
        BType parseBType();
        ConstDef parseConstDef();
        ConstInitVal parseConstInitVal();
        VarDecl parseVarDecl();
        VarDef parseVarDef();
        InitVal parseInitVal();
        FuncDef parseFuncDef();
        MainFuncDef parseMainFuncDef();
        FuncType parseFuncType();
        FuncFParams parseFuncFParams();
        FuncFParam parseFuncFParam();
        Block parseBlock();
        BlockItem parseBlockItem();
        Stmt parseStmt();
        Exp parseExp();
        Cond parseCond();
        LVal parseLVal();
        PrimaryExp parsePrimaryExp();
        Number parseNumber();
        UnaryExp parseUnaryExp();
        FuncRParams parseFuncRParams();
        MulExp parseMulExp();
        AddExp parseAddExp();
        RelExp parseRelExp();
        EqExp parseEqExp();
        LAndExp parseLAndExp();
        LOrExp parseLOrExp();
        ConstExp parseConstExp();
        IntConst parseIntConst();
        Ident parseIdent();
        FormatString parseFormatString();
        UnaryOp parseUnaryOp();

        std::string getSymbol(int bias);
        std::string getString(int bias);
    };
}

#endif //COMPILER_PARSER_H
