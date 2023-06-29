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

    virtual std::string dump() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const BaseASTNode& node);
};

// BType -> 'int'
class BType : public BaseASTNode {
public:
    enum Type {
        INT,
    };

    explicit BType() = default;
    explicit BType(Type type);

    std::string dump() const override;

private:
    Type type{};

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

    std::string dump() const override;

private:
    Type type{};

};

// IntConst
class IntConst : public BaseASTNode {
public:
    explicit IntConst() = default;
    explicit IntConst(const Token& token);

    std::string dump() const override;

private:
    Token token;

};

// Ident
class Ident : public BaseASTNode {
public:
    explicit Ident() = default;
    explicit Ident(const Token& token);

    std::string dump() const override;

private:
    Token token;

};

// FormatString
class FormatString : public BaseASTNode {
public:
    explicit FormatString() = default;
    explicit FormatString(const Token& token);

    std::string dump() const override;

private:
    Token token;

};

// UnaryOp
class UnaryOp : public BaseASTNode {
public:
    explicit UnaryOp() = default;
    explicit UnaryOp(const Token& token);

    std::string dump() const override;

private:
    Token token;

};

// Number -> IntConst
class Number : public BaseASTNode {
public:
    explicit Number() = default;
    explicit Number(const IntConst& intConst);

    std::string dump() const override;

private:
    IntConst intConst;

};

// FuncFParam -> BType Ident ['[' ']' { '[' ConstExp ']' }]
class FuncFParam : public BaseASTNode {
public:
    explicit FuncFParam() = default;
    explicit FuncFParam(const BType& bType,
                        const Ident& ident);
    explicit FuncFParam(const BType& bType,
                        const Ident& ident,
                        const std::vector<ConstExp>& constExps);

    std::string dump() const override;

private:
    BType bType;
    Ident ident;
    std::vector<ConstExp> constExps;
    bool isArray{};

};

// FuncFParams -> FuncFParam { ',' FuncFParam }
class FuncFParams : public BaseASTNode {
public:
    explicit FuncFParams() = default;
    explicit FuncFParams(const std::vector<FuncFParam>& funcFParams);

    std::string dump() const override;

private:
    std::vector<FuncFParam> funcFParams;

};

// Block
class Block : public BaseASTNode {
public:
    explicit Block() = default;
    explicit Block(const std::vector<BlockItem>& blockItems);

    std::string dump() const override;

public:
    std::vector<BlockItem> blockItems;

};

// FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
class FuncDef : public BaseASTNode{
public:
    explicit FuncDef() = default;
    explicit FuncDef(const FuncType& funcType,
                     const Ident& ident,
                     const Block& block);
    explicit FuncDef(const FuncType& funcType,
                     const Ident& ident,
                     const FuncFParams& funcFParams,
                     const Block& block);

    std::string dump() const override;

private:
    FuncType funcType;
    Ident ident;
    FuncFParams funcFParams;
    Block block;

    bool hasParams{};

};

// MainFuncDef -> 'int' 'main' '(' ')' Block
class MainFuncDef : public BaseASTNode {
public:
    explicit MainFuncDef() = default;
    explicit MainFuncDef(const Block& block);

    std::string dump() const override;

private:
    Block block;
};

// ConstExp → AddExp
class ConstExp : public BaseASTNode {
public:
    explicit ConstExp() = default;
    explicit ConstExp(const AddExp& addExp);

    std::string dump() const override;

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

    std::string dump() const override;

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

    std::string dump() const override;

private:
    ConstExp exp;
    std::vector<InitVal> initVals;

    Type type{};
};

// VarDef -> Ident { '[' ConstExp ']' }
//         | Ident { '[' ConstExp ']' } '=' InitVal
class VarDef : public BaseASTNode {
public:
    explicit VarDef() = default;
    explicit VarDef(const Ident& ident,
                    const std::vector<ConstExp>& constExps);
    explicit VarDef(const Ident& ident,
                    const std::vector<ConstExp>& constExps,
                    const InitVal& initVal);

    std::string dump() const override;

private:
    Ident ident;
    std::vector<ConstExp> constExps;
    InitVal initVal;

    bool isInit{};

};

//  ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal
class ConstDef : public BaseASTNode {
public:
    explicit ConstDef() = default;
    explicit ConstDef(const Ident& ident,
                      const std::vector<ConstExp>& constExps,
                      const ConstInitVal& constInitVal);

    std::string dump() const override;

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

    std::string dump() const override;


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

    std::string dump() const override;

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

    std::string dump() const override;

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

    std::string dump() const override;

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

    std::string dump() const override;

private:
    Decl decl;
    Stmt stmt;

    Type type{};
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
public:
    explicit Exp() = default;
    explicit Exp(const AddExp& addExp);

    std::string dump() const override;

private:
    AddExp addExp;
};

// FuncRParams -> Exp { ',' Exp }
class FuncRParams : public BaseASTNode {
public:
    explicit FuncRParams() = default;
    explicit FuncRParams(const std::vector<Exp>& exps);

    std::string dump() const override;

private:
    std::vector<Exp> exps;

};

// LVal -> Ident {'[' Exp ']'}
class LVal : public BaseASTNode {
public:
    explicit LVal() = default;
    explicit LVal(const Ident& ident,
                  const std::vector<Exp>& exps);

    std::string dump() const override;

private:
    Ident ident;
    std::vector<Exp> exps;

};

// PrimaryExp -> '(' Exp ')' | LVal | Number
class PrimaryExp : public BaseASTNode {
public:
    enum Type {
        EXP,
        LVAL,
        NUM,
    };

    explicit PrimaryExp() = default;
    explicit PrimaryExp(const Exp& exp);
    explicit PrimaryExp(const LVal& lVal);
    explicit PrimaryExp(const Number& number);

    std::string dump() const override;

private:
    Exp exp;
    LVal lVal;
    Number number;

    Type type{};
};

// UnaryExp -> PrimaryExp
//           | Ident '(' [FuncRParams] ')'
//           | UnaryOp UnaryExp
class UnaryExp : public BaseASTNode {
public:
    enum Type {
        PRI,
        IDE,
        UNA,
    };

    explicit UnaryExp() = default;
    explicit UnaryExp(const PrimaryExp& primaryExp);
    explicit UnaryExp(const Ident& ident);
    explicit UnaryExp(const Ident& ident,
                      const FuncRParams& funcRParams);
    explicit UnaryExp(const UnaryOp& unaryOp,
                      const UnaryExp& unaryExp);

    std::string dump() const override;

private:
    PrimaryExp primaryExp;

    Ident ident;
    FuncRParams funcRParams;
    bool hasParams{};

    UnaryOp unaryOp;
    UnaryExp unaryExp;

    Type type{};
};

// MulExp -> UnaryExp { ('*' | '/' | '%') UnaryExp }
class MulExp : public BaseASTNode {
public:

private:

};

class Ast {
public:
    std::vector<CompUnit> units;


};





#endif //COMPILER_AST_H
