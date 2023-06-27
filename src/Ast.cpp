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
CompUnit::CompUnit(const std::vector<Decl> &decls,
                   const std::vector<FuncDef> &funcDefs,
                   const MainFuncDef &mainFuncDef) {
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
    for (auto iter = constExps.begin(); iter != constExps.end(); iter++) {
        std::cout << "[";
        iter->dump();
        std::cout << "]";
    }
    constInitVal.dump();
    std::cout << " }";
}
