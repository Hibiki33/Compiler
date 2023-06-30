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

namespace Front {

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

        friend std::ostream &operator<<(std::ostream &os, const BaseASTNode &node);
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

        explicit IntConst(const Token &token);

        std::string dump() const override;

    private:
        Token token;

    };

// Ident
    class Ident : public BaseASTNode {
    public:
        explicit Ident() = default;

        explicit Ident(const Token &token);

        std::string dump() const override;

    private:
        Token token;

    };

// FormatString
    class FormatString : public BaseASTNode {
    public:
        explicit FormatString() = default;

        explicit FormatString(const Token &token);

        std::string dump() const override;

    private:
        Token token;

    };

// UnaryOp
    class UnaryOp : public BaseASTNode {
    public:
        explicit UnaryOp() = default;

        explicit UnaryOp(const Token &token);

        std::string dump() const override;

    private:
        Token token;

    };

// Number -> IntConst
    class Number : public BaseASTNode {
    public:
        explicit Number() = default;

        explicit Number(const IntConst &intConst);

        std::string dump() const override;

    private:
        IntConst intConst;

    };

// FuncFParam -> BType Ident ['[' ']' { '[' ConstExp ']' }]
    class FuncFParam : public BaseASTNode {
    public:
        explicit FuncFParam() = default;

        explicit FuncFParam(const BType &bType,
                            const Ident &ident);

        explicit FuncFParam(const BType &bType,
                            const Ident &ident,
                            const std::vector<ConstExp> &constExps);

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

        explicit FuncFParams(const std::vector<FuncFParam> &funcFParams);

        std::string dump() const override;

    private:
        std::vector<FuncFParam> funcFParams;

    };

// Block
    class Block : public BaseASTNode {
    public:
        explicit Block() = default;

        explicit Block(const std::vector<BlockItem> &blockItems);

        std::string dump() const override;

    public:
        std::vector<BlockItem> blockItems;

    };

// FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
    class FuncDef : public BaseASTNode {
    public:
        explicit FuncDef() = default;

        explicit FuncDef(const FuncType &funcType,
                         const Ident &ident,
                         const Block &block);

        explicit FuncDef(const FuncType &funcType,
                         const Ident &ident,
                         const FuncFParams &funcFParams,
                         const Block &block);

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

        explicit MainFuncDef(const Block &block);

        std::string dump() const override;

    private:
        Block block;
    };

// ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
    class ConstDecl : public BaseASTNode {
    public:
        explicit ConstDecl() = default;

        explicit ConstDecl(const BType &bType,
                           const std::vector<ConstDef> &constDefs);

        std::string dump() const override;


    private:
        BType bType;
        std::vector<ConstDef> constDefs;

    };

// VarDecl -> BType VarDef { ',' VarDef } ';'
    class VarDecl : public BaseASTNode {
    public:
        explicit VarDecl() = default;

        explicit VarDecl(const BType &bType,
                         const std::vector<VarDef> &varDefs);

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

        explicit Decl(const ConstDecl &constDecl);

        explicit Decl(const VarDecl &varDecl);

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
        enum Type {
            ASSIGNEXP,
            EXP,
            BLOCK,
            BRANCH,
            LOOP,
            BREAK,
            RETURN,
            INPUT,
            OUTPUT,
            NONE,
        };

        explicit Stmt() = default;

        explicit Stmt(const std::vector<BaseASTNode *> &stmtNodes,
                      Type type);

        std::string dump() const override;

    private:
        std::vector<BaseASTNode *> stmtNodes;

        Type type{};
    };

// BlockItem -> Decl | Stmt
    class BlockItem : public BaseASTNode {
    public:
        enum Type {
            DECL,
            STMT,
        };

        explicit BlockItem() = default;

        explicit BlockItem(const Decl &decl);

        explicit BlockItem(const Stmt &stmt);

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

        explicit CompUnit(const std::vector<Decl> &decls,
                          const std::vector<FuncDef> &funcDefs,
                          const MainFuncDef &mainFuncDef);

        std::string dump() const override;

    private:
        std::vector<Decl> decls;
        std::vector<FuncDef> funcDefs;
        MainFuncDef mainFuncDef;

    };

// FuncRParams -> Exp { ',' Exp }
    class FuncRParams : public BaseASTNode {
    public:
        explicit FuncRParams() = default;

        explicit FuncRParams(const std::vector<Exp> &exps);

        std::string dump() const override;

    private:
        std::vector<Exp> exps;

    };

// LVal -> Ident {'[' Exp ']'}
    class LVal : public BaseASTNode {
    public:
        explicit LVal() = default;

        explicit LVal(const Ident &ident,
                      const std::vector<Exp> &exps);

        std::string dump() const override;

    private:
        Ident ident;
        std::vector<Exp> exps;

    };

// MulExp -> UnaryExp { ('*' | '/' | '%') UnaryExp }
    class MulExp : public BaseASTNode {
    public:
        explicit MulExp() = default;

        explicit MulExp(const std::vector<UnaryExp> &unaryExps,
                        const std::vector<Token> &ops);

        std::string dump() const override;

    private:
        std::vector<UnaryExp> unaryExps;
        std::vector<Token> ops;

    };

// AddExp -> MulExp { ('+' | '-') MulExp }
    class AddExp : public BaseASTNode {
    public:
        explicit AddExp() = default;

        explicit AddExp(const std::vector<MulExp> &mulExps,
                        const std::vector<Token> &ops);

        std::string dump() const override;

    private:
        std::vector<MulExp> mulExps;
        std::vector<Token> ops;

    };

// RelExp -> AddExp { ('<' | '>' | '<=' | '>=') AddExp }
    class RelExp : public BaseASTNode {
    public:
        explicit RelExp() = default;

        explicit RelExp(const std::vector<AddExp> &addExps,
                        const std::vector<Token> &ops);

        std::string dump() const override;

    private:
        std::vector<AddExp> addExps;
        std::vector<Token> ops;

    };

// EqExp -> RelExp { ('==' | '!=') RelExp }
    class EqExp : public BaseASTNode {
    public:
        explicit EqExp() = default;

        explicit EqExp(const std::vector<RelExp> &relExps,
                       const std::vector<Token> &ops);

        std::string dump() const override;

    private:
        std::vector<RelExp> relExps;
        std::vector<Token> ops;

    };

// LAndExp -> EqExp { '&&' EqExp }
    class LAndExp : public BaseASTNode {
    public:
        explicit LAndExp() = default;

        explicit LAndExp(const std::vector<EqExp> &eqExps,
                         const std::vector<Token> &ops);

        std::string dump() const override;

    private:
        std::vector<EqExp> eqExps;
        std::vector<Token> ops;

    };

// LOrExp -> LAndExp { '||' LAndExp }
    class LOrExp : public BaseASTNode {
    public:
        explicit LOrExp() = default;

        explicit LOrExp(const std::vector<LAndExp> &lAndExps,
                        const std::vector<Token> &ops);

        std::string dump() const override;

    private:
        std::vector<LAndExp> lAndExps;
        std::vector<Token> ops;

    };

// Cond -> LOrExp
    class Cond : public BaseASTNode {
    public:
        explicit Cond() = default;

        explicit Cond(const LOrExp &lOrExp);

        std::string dump() const override;

    private:
        LOrExp lOrExp;

    };

// ConstExp → AddExp
    class ConstExp : public BaseASTNode {
    public:
        explicit ConstExp() = default;

        explicit ConstExp(const AddExp &addExp);

        std::string dump() const override;

    private:
        AddExp addExp;

    };

// Exp -> AddExp
    class Exp : public BaseASTNode {
    public:
        explicit Exp() = default;

        explicit Exp(const AddExp &addExp);

        std::string dump() const override;

    private:
        AddExp addExp;
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

        explicit PrimaryExp(const Exp &exp);

        explicit PrimaryExp(const LVal &lVal);

        explicit PrimaryExp(const Number &number);

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

//    explicit UnaryExp(const PrimaryExp& primaryExp);
//    explicit UnaryExp(const Ident& ident);
//    explicit UnaryExp(const Ident& ident,
//                      const FuncRParams& funcRParams);
//    explicit UnaryExp(const UnaryOp& unaryOp,
//                      UnaryExp unaryExp);
        explicit UnaryExp(const std::vector<BaseASTNode *> &unaryExpNodes,
                          UnaryExp::Type type);

        std::string dump() const override;

    private:
//    PrimaryExp primaryExp;
//
//    Ident ident;
//    FuncRParams funcRParams;
//    bool hasParams{};
//
//    UnaryOp unaryOp;
//    UnaryExp* unaryExp{};

        std::vector<BaseASTNode *> unaryExpNodes;

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

        explicit InitVal(const Exp &exp);

        explicit InitVal(const std::vector<InitVal> &initVals);

        std::string dump() const override;

    private:
        Exp exp;
        std::vector<InitVal> initVals;

        Type type{};
    };

// VarDef -> Ident { '[' ConstExp ']' }
//         | Ident { '[' ConstExp ']' } '=' InitVal
    class VarDef : public BaseASTNode {
    public:
        explicit VarDef() = default;

        explicit VarDef(const Ident &ident,
                        const std::vector<ConstExp> &constExps);

        explicit VarDef(const Ident &ident,
                        const std::vector<ConstExp> &constExps,
                        const InitVal &initVal);

        std::string dump() const override;

    private:
        Ident ident;
        std::vector<ConstExp> constExps;
        InitVal initVal;

        bool isInit{};

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

        explicit ConstInitVal(const ConstExp &constExp);

        explicit ConstInitVal(const std::vector<ConstInitVal> &constInitVals);

        std::string dump() const override;

    private:
        ConstExp constExp;
        std::vector<ConstInitVal> constInitVals;

        Type type{};
    };

//  ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal
    class ConstDef : public BaseASTNode {
    public:
        explicit ConstDef() = default;

        explicit ConstDef(const Ident &ident,
                          const std::vector<ConstExp> &constExps,
                          const ConstInitVal &constInitVal);

        std::string dump() const override;

    private:
        Ident ident;
        std::vector<ConstExp> constExps;
        ConstInitVal constInitVal;

    };

    // Ast, simply a 'CompUnit'
    class Ast {
    public:
        explicit Ast() = default;
        explicit Ast(const CompUnit& unit);
        ~Ast() = default;

    private:
        CompUnit unit;
    };
}

#endif //COMPILER_AST_H
