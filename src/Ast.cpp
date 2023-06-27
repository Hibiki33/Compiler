//
// Created by 11678 on 2023/6/26.
//

#include "Ast.h"

/*
 * class BType
 */
BType::BType(BType::Type type) {
    this->type = type;
}

void BType::dump() const {
    std::cout << "BType { ";
    if (type == INT) {
        std::cout << "int";
    }
    std::cout << " }";
}

/*
 * class FuncType
 */
FuncType::FuncType(FuncType::Type type) {
    this->type = type;
}

void FuncType::dump() const {
    std::cout << "FuncType { ";
    if (type == VOID) {
        std::cout << "void";
    } else if (type == INT) {
        std::cout << "int";
    }
    std::cout << " }";
}

/*
 * class IntConst
 */
IntConst::IntConst(const Token& token) {
    this->token = token;
}

void IntConst::dump() const {
    std::cout << "IntConst { ";
    std::cout << token;
    std::cout << " }";
}

/*
 * class Ident
 */
Ident::Ident(const Token &token) {
    this->token = token;
}

void Ident::dump() const {
    std::cout << "Ident { ";
    std::cout << token;
    std::cout << " }";
}

/*
 * class FormatString
 */

FormatString::FormatString(const Token &token) {
    this->token = token;
}

void FormatString::dump() const {
    std::cout << "FormatString { ";
    std::cout << token;
    std::cout << " }";
}

/*
 * class UnaryOp
 */
UnaryOp::UnaryOp(const Token &token) {
    this->token = token;
}

void UnaryOp::dump() const {
    std::cout << "UnaryOp { ";
    std::cout << token;
    std::cout << " }";
}

/*
 * class Number
 */
Number::Number(const IntConst &intConst) {
    this->intConst = intConst;
}

void Number::dump() const {
    std::cout << "UnaryOp { ";
    intConst.dump();
    std::cout << " }";
}

/*
 * class Decl
 */
Decl::Decl(const ConstDecl &constDecl) {
    this->constDecl = constDecl;
    type = CONSTDECL;
}

Decl::Decl(const VarDecl &varDecl) {
    this->varDecl = varDecl;
    type = VARDECL;
}

void Decl::dump() const {
    std::cout << "Decl { ";
    if (type == CONSTDECL) {
        constDecl.dump();
    } else {
        varDecl.dump();
    }
    std::cout << " }";
}

/*
 * Def
 */

/*
 * class MainFuncDef
 */
MainFuncDef::MainFuncDef(const Block& block) {
    this->block = block;
}

void MainFuncDef::dump() const {
    std::cout << "MainFuncDef { ";
    std::cout << "int main()";
    block.dump();
    std::cout << " }";
}

/*
 * class Block
 */
void Block::dump() const {
    std::cout << "Block { ";

    std::cout << " }";
}

/*
 * class CompUnit
 */
CompUnit::CompUnit(const std::vector<Decl>& decls,
                   const std::vector<FuncDef>& funcDefs,
                   const MainFuncDef& mainFuncDef) {
    this->decls = decls;
    this->funcDefs = funcDefs;
    this->mainFuncDef = mainFuncDef;
}

/*
 * class BlockItem
 */
BlockItem::BlockItem(const Decl &decl) {
    this->decl = decl;
    type = DECL;
}

BlockItem::BlockItem(const Stmt &stmt) {
    this->stmt = stmt;
    type = STMT;
}

void BlockItem::dump() const {
    std::cout << "BlockItem { ";
    if (type == DECL) {
        decl.dump();
    } else {
        stmt.dump();
    }
    std::cout << " }";
}

/*
 * class ConstDecl
 */
ConstDecl::ConstDecl(const BType &bType,
                     const std::vector<ConstDef>& constDefs) {
    this->bType = bType;
    this->constDefs = constDefs;
}

void ConstDecl::dump() const {
    std::cout << "ConstDecl { ";
    std::cout << "const";
    bType.dump();
    for (auto iter = constDefs.begin(); iter != constDefs.end(); iter++) {
        if (std::next(iter, 1) != constDefs.end()) {
            iter->dump();
            std::cout << ", ";
        } else {
            iter->dump();
        }
    }
    std::cout << ";";
    std::cout << " }";
}

/*
 * class ConstDef
 */
ConstDef::ConstDef(const Ident& ident,
                   const std::vector<ConstExp>& constExps,
                   const ConstInitVal& constInitVal) {
    this->ident = ident;
    this->constExps = constExps;
    this->constInitVal = constInitVal;
}

void ConstDef::dump() const {
    std::cout << "ConstDef { ";
    ident.dump();
    for (const auto & constExp : constExps) {
        std::cout << "[";
        constExp.dump();
        std::cout << "]";
    }
    std::cout << "=";
    constInitVal.dump();
    std::cout << " }";
}

/*
 * class ConstInitVal
 */
ConstInitVal::ConstInitVal(const ConstExp& constExp) {
    this->constExp = constExp;
    type = EXP;
}

ConstInitVal::ConstInitVal(const std::vector<ConstInitVal>& constInitVals) {
    this->constInitVals = constInitVals;
    type = ARR;
}

void ConstInitVal::dump() const {
    std::cout << "ConstInitVal { ";
    if (type == EXP) {
        constExp.dump();
    } else {
        std::cout << "{";
        for (auto iter = constInitVals.begin(); iter != constInitVals.end(); iter++) {
            if (std::next(iter, 1) != constInitVals.end()) {
                iter->dump();
                std::cout << ", ";
            } else {
                iter->dump();
            }
        }
        std::cout << "}";
    }
    std::cout << " }";
}

/*
 * class InitVal
 */
InitVal::InitVal(const Exp& exp) {
    this->exp = exp;
    type = EXP;
}

InitVal::InitVal(const std::vector<InitVal>& initVals) {
    this->initVals = initVals;
    type = ARR;
}

void InitVal::dump() const {
    std::cout << "InitVal { ";
    if (type == EXP) {
        exp.dump();
    } else {
        std::cout << "{";
        for (auto iter = initVals.begin(); iter != initVals.end(); iter++) {
            if (std::next(iter, 1) != initVals.end()) {
                iter->dump();
                std::cout << ", ";
            } else {
                iter->dump();
            }
        }
        std::cout << "}";
    }
    std::cout << " }";
}

/*
 * class ConstExp
 */
ConstExp::ConstExp(const AddExp &addExp) {
    this->addExp = addExp;
}

void ConstExp::dump() const {
    std::cout << "ConstExp { ";
    addExp.dump();
    std::cout << " }";
}

/*
 * class VarDecl
 */
VarDecl::VarDecl(const BType &bType,
                 const std::vector<VarDef> &varDefs) {
    this->bType = bType;
    this->varDefs = varDefs;
}

void VarDecl::dump() const {
    std::cout << "VarDecl { ";
    bType.dump();
    for (auto iter = varDefs.begin(); iter != varDefs.end(); iter++) {
        if (std::next(iter, 1) != varDefs.end()) {
            iter->dump();
            std::cout << ", ";
        } else {
            iter->dump();
        }
    }
    std::cout << " }";
}

/*
 * class VarDef
 */
VarDef::VarDef(const Ident& ident,
               const std::vector<ConstExp>& constExps) {
    this->ident = ident;
    this->constExps = constExps;
    isInit = false;
}

VarDef::VarDef(const Ident& ident,
               const std::vector<ConstExp>& constExps,
               const InitVal& initVal) {
    this->ident = ident;
    this->constExps = constExps;
    this->initVal = initVal;
    isInit = true;
}

void VarDef::dump() const {
    std::cout << "VarDef { ";
    ident.dump();
    for (const auto & constExp : constExps) {
        std::cout << "[";
        constExp.dump();
        std::cout << "]";
    }
    std::cout << " }";
}

/*
 * FuncDef
 */
FuncDef::FuncDef(const FuncType& funcType,
                 const Ident& ident,
                 const FuncFParams& funcFParams,
                 const Block& block) {
    this->funcType = funcType;
    this->ident = ident;
    this->funcFParams = funcFParams;
    this->block = block;
}

void FuncDef::dump() const {
    std::cout << "FuncDef { ";
    funcType.dump();
    ident.dump();
    std::cout << "(";
    funcFParams.dump();
    std::cout << ")";
    block.dump();
    std::cout << " }";
}
