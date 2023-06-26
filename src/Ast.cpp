//
// Created by 11678 on 2023/6/26.
//

#include "Ast.h"

/*
 * Decl
 */
Decl::Decl(bool constant, const Token& bType, const std::vector<Def> &defs) {
    this->constant = constant;
    this->bType = bType;
    this->defs = defs;
}

Decl::~Decl() = default;

bool Decl::isConstant() const {
    return constant;
}

Token Decl::getBType() {
    return bType;
}

std::vector<Def> Decl::getDefs() {
    return defs;
}


