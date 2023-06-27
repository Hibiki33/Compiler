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
 * class Decl
 */
Decl::Decl(bool constant, const Token& bType, const std::vector<Def> &defs) {
    this->constant = constant;
    this->bType = bType;
    this->defs = defs;
}

bool Decl::isConstant() const {
    return constant;
}

Token Decl::getBType() {
    return bType;
}

std::vector<Def> Decl::getDefs() {
    return defs;
}

void Decl::dump() const {

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


