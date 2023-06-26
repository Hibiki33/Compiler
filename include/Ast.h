//
// Created by 11678 on 2023/6/26.
//

#ifndef COMPILER_AST_H
#define COMPILER_AST_H

#pragma once
#include <vector>
#include <string>
#include "Token.h"

class CompUnit;
class Decl;
class Def;
class ConstDecl;
class BType;
class ConstDef;



// CompUnit -> Decl | FuncDef
class CompUnit {

};

// BlockItem -> Decl | Stmt
class BlockItem {

};

// Def -> Ident {'[' Exp ']'} ['=' Init]
class Def {
public:

private:

};

// Decl -> ('const') 'int' Def {',' Def} ';'
class Decl : public CompUnit, public BlockItem {
public:
    explicit Decl(bool constant, const Token& bType, const std::vector<Def>& defs);
    ~Decl();

    bool isConstant() const;
    Token getBType();
    std::vector<Def> getDefs();

private:
    bool constant;
    Token bType;
    std::vector<Def> defs;
};


class Ast {
public:
    std::vector<CompUnit> units;


};






#endif //COMPILER_AST_H
