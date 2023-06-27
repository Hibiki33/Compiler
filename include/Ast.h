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

class CompUnit;
class Decl;
class ConstDecl;
class BType;
class ConstDef;
class ConstInitVal;
class VarDecl;
class VarDef;
class InitVal;
class FuncDef;
class MainFuncDef;
class FuncType;
class FuncFParams;
class FuncFParam;
class Block;
class BlockItem;
class Stmt;
class Exp;
class Cond;
class LVal;
class PrimaryExp;
class Number;
class UnaryExp;
class FuncRParams;
class MulExp;
class AddExp;
class RelExp;
class EqExp;
class LAndExp;
class LOrExp;
class ConstExp;

class IntConst;
class Ident;
class FormatString;
class UnaryOp;


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

// UnaryOp
class UnaryOp : public BaseASTNode {
public:
    explicit UnaryOp() = default;
    explicit UnaryOp(const Token& token);

    void dump() const override;

private:
    Token token;

};

// Number -> IntConst
class Number : public BaseASTNode {
public:
    explicit Number() = default;
    explicit Number(const IntConst& intConst);

    void dump() const override;

private:
    IntConst intConst;

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

// ConstExp → AddExp
class ConstExp : public BaseASTNode {
public:
    explicit ConstExp() = default;
    explicit ConstExp(const AddExp& addExp);

    void dump() const override;

private:
    AddExp addExp;

};

// ConstInitVal -> ConstExp
//              | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
class ConstInitVal : public BaseASTNode {
public:
    enum Type {
        EXP,
        ARR,
    };

    explicit ConstInitVal() = default;
    explicit ConstInitVal(const ConstExp& constExp);
    explicit ConstInitVal(const std::vector<ConstInitVal>& constInitVals);

    void dump() const override;

private:
    ConstExp constExp;
    std::vector<ConstInitVal> constInitVals;

    Type type{};
};

// InitVal -> Exp | '{' [ InitVal { ',' InitVal } ] '}'
class InitVal : public BaseASTNode {
public:
    enum Type {
        EXP,
        ARR,
    };

    explicit InitVal() = default;
    explicit InitVal(const Exp& exp);
    explicit InitVal(const std::vector<InitVal>& initVals);

    void dump() const override;

private:
    ConstExp exp;
    std::vector<InitVal> initVals;

    Type type{};
};


//  ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal
class ConstDef : public BaseASTNode {
public:
    explicit ConstDef() = default;
    explicit ConstDef(const Ident& ident,
                      const std::vector<ConstExp>& constExps,
                      const ConstInitVal& constInitVal);

    void dump() const override;

private:
    Ident ident;
    std::vector<ConstExp> constExps;
    ConstInitVal constInitVal;

};

// ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
class ConstDecl : public BaseASTNode {
public:
    explicit ConstDecl() = default;
    explicit ConstDecl(const BType& bType,
                       const std::vector<ConstDef>& constDefs);

    void dump() const override;


private:
    BType bType;
    std::vector<ConstDef> constDefs;

};

// VarDecl -> BType VarDef { ',' VarDef } ';'
class VarDecl : public BaseASTNode {
public:
    explicit VarDecl() = default;
    explicit VarDecl(const BType& bType,
                     const std::vector<VarDef>& varDefs);

    void dump() const override;

private:
    BType bType;
    std::vector<VarDef> varDefs;

};

// Decl -> ConstDecl | VarDecl;
class Decl : public BaseASTNode {
public:
    enum Type {
        CONSTDECL,
        VARDECL,
    };

    explicit Decl() = default;
    explicit Decl(const ConstDecl& constDecl);
    explicit Decl(const VarDecl& varDecl);

    void dump() const override;

private:
    ConstDecl constDecl;
    VarDecl varDecl;

    Type type{};
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
    enum Type {
        DECL,
        STMT,
    };

    explicit BlockItem() = default;
    explicit BlockItem(const Decl& decl);
    explicit BlockItem(const Stmt& stmt);

    void dump() const override;

private:
    Decl decl;
    Stmt stmt;

    Type type;
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



// Exp -> AddExp
class Exp : public BaseASTNode {

};







class Ast {
public:
    std::vector<CompUnit> units;


};






#endif //COMPILER_AST_H
