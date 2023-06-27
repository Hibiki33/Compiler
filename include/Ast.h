//
// Created by 11678 on 2023/6/26.
//

#ifndef COMPILER_AST_H
#define COMPILER_AST_H

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Token.h"

class BaseASTNode;
class BType;
class FuncType;

class IntConst;
class Ident;
class FormatString;

class CompUnit;
class Decl;
class Def;
class ConstDecl;
class BType;
class ConstDef;
class Init;
class FuncDef;
class MainFuncDef;
class Block;
class Stmt;

class BaseASTNode {
public:
    virtual  ~BaseASTNode() = default;

    virtual void dump() const = 0;
};

// BType -> 'int'
class BType : public BaseASTNode {
public:
    enum Type {
        INT,
    };

    explicit BType() = default;
    explicit BType(Type type);

    void dump() const override;

private:
    Type type;

};

// FuncType -> 'void' | 'int'
class FuncType : public BaseASTNode {
public:
    enum Type {
        VOID,
        INT,
    };

    explicit FuncType() = default;
    explicit FuncType(Type type);

    void dump() const override;

private:
    Type type;

};

// IntConst
class IntConst : public BaseASTNode {
public:
    explicit IntConst() = default;
    explicit IntConst(const Token& token);

    void dump() const override;

private:
    Token token;

};

// Ident
class Ident : public BaseASTNode {
public:
    explicit Ident() = default;
    explicit Ident(const Token& token);

    void dump() const override;

private:
    Token token;

};

// FormatString
class FormatString : public BaseASTNode {
public:
    explicit FormatString() = default;
    explicit FormatString(const Token& token);

    void dump() const override;

private:
    Token token;

};

// Number -> IntConst
class Number : public BaseASTNode {
public:


private:


};


// Def -> Ident {'[' Exp ']'} ['=' Init]
class Def {
public:

private:

};

// FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
class FuncDef {
public:

private:

};

// Block
class Block : public BaseASTNode {
public:
    void dump() const override;

public:

};

// MainFuncDef -> 'int' 'main' '(' ')' Block
class MainFuncDef : public BaseASTNode {
public:
    explicit MainFuncDef() = default;
    explicit MainFuncDef(const Block& block);

    void dump() const override;

private:
    Block block;
};

// Decl -> ('const') 'int' Def {',' Def} ';'
class Decl : public BaseASTNode {
public:
    explicit Decl() = default;
    explicit Decl(bool constant, const Token& bType, const std::vector<Def>& defs);

    void dump() const override;

    bool isConstant() const;
    Token getBType();
    std::vector<Def> getDefs();

private:
    bool constant{};
    Token bType;
    std::vector<Def> defs;
};

// Stmt -> LVal '=' Exp ';'
//      | [Exp] ';'
//      | Block
//      | 'if' '(' Cond ')' Stmt [ 'else' Stmt ]
//      | 'while' '(' Cond ')' Stmt
//      | 'break' ';' | 'continue' ';'
//      | 'return' [Exp] ';'
//      | LVal '=' 'getint''('')'';'
//      | 'printf''('FormatString{','Exp}')'';'
class Stmt : public BaseASTNode {
public:

    void dump() const override;

private:

};

// BlockItem -> Decl | Stmt
class BlockItem : public BaseASTNode {
public:
    explicit BlockItem() = default;
    explicit BlockItem(const Decl& decl);
    explicit BlockItem(const Stmt& stmt);

    void dump() const override;

private:
    Decl decl;
    Stmt stmt;

#define DECL true
#define STMT false
    bool type = false;
};

// CompUnit ->  {Decl} {FuncDef} MainFuncDef
class CompUnit : public BaseASTNode {
public:
    explicit CompUnit() = default;
    explicit CompUnit(const std::vector<Decl>& decls,
                      const std::vector<FuncDef>& funcDefs,
                      const MainFuncDef& mainFuncDef);

private:
    std::vector<Decl> decls;
    std::vector<FuncDef> funcDefs;
    MainFuncDef mainFuncDef;


};










// Init -> Exp | InitArray
class Init {

};

// Exp -> AddExp
class Exp : public Init {

};







class Ast {
public:
    std::vector<CompUnit> units;


};






#endif //COMPILER_AST_H
