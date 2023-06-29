//
// Created by 11678 on 2023/6/26.
//

#include "Ast.h"

/*
 * class BaseASTNode
 */
std::ostream& operator<<(std::ostream& os, const BaseASTNode& node) {
    os << node.dump();
    return os;
}

/*
 * class BType
 */
BType::BType(BType::Type type) {
    this->type = type;
}

std::string BType::dump() const {
    return "BType { " +
    std::string(type == INT ? "int" : "") +
    " }";
}

/*
 * class FuncType
 */
FuncType::FuncType(FuncType::Type type) {
    this->type = type;
}

std::string FuncType::dump() const {
    return "FuncType { " +
    std::string(type == VOID ? "void" :
                type == INT ? "int" : "") +
    " }";
}

/*
 * class IntConst
 */
IntConst::IntConst(const Token& token) {
    this->token = token;
}

std::string IntConst::dump() const {
    return "IntConst { " +
    token.getTokenSymbol() + " : " +
    token.getTokenString() +
    " }";
}

/*
 * class Ident
 */
Ident::Ident(const Token &token) {
    this->token = token;
}

std::string Ident::dump() const {
    return "Ident { " +
    token.getTokenSymbol() + " : " +
    token.getTokenString() +
    " }";
}

/*
 * class FormatString
 */

FormatString::FormatString(const Token &token) {
    this->token = token;
}

std::string FormatString::dump() const {
    return "FormatString { " +
    token.getTokenSymbol() + " : " +
    token.getTokenString() +
    " }";
}

/*
 * class UnaryOp
 */
UnaryOp::UnaryOp(const Token &token) {
    this->token = token;
}

std::string UnaryOp::dump() const {
    return "UnaryOp { " +
    token.getTokenSymbol() + " : " +
    token.getTokenString() +
    " }";
}

/*
 * class Number
 */
Number::Number(const IntConst &intConst) {
    this->intConst = intConst;
}

std::string Number::dump() const {
    return "UnaryOp { " +
    intConst.dump() +
    " }";
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

std::string Decl::dump() const {
    return "Decl { " +
    std::string(type == CONSTDECL ? constDecl.dump() :
                type == VARDECL ? varDecl.dump() : "") +
    " }";
}

/*
 * class MainFuncDef
 */
MainFuncDef::MainFuncDef(const Block& block) {
    this->block = block;
}

std::string MainFuncDef::dump() const {
    return "MainFuncDef { " +
    std::string("int main() ") +
    block.dump() +
    " }";
}

/*
 * class Block
 */
Block::Block(const std::vector<BlockItem> &blockItems) {
    this->blockItems = blockItems;
}

std::string Block::dump() const {
    std::string res =  "Block { " +
    std::string("{");
    for (const auto & blockItem : blockItems) {
         res += blockItem.dump();
    }
    return res + "}" +
    " }";
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

std::string BlockItem::dump() const {
    return "BlockItem { " +
    std::string(type == DECL ? decl.dump() :
                type == STMT ? stmt.dump() : "") +
    " }";
}

/*
 * class ConstDecl
 */
ConstDecl::ConstDecl(const BType &bType,
                     const std::vector<ConstDef>& constDefs) {
    this->bType = bType;
    this->constDefs = constDefs;
}

std::string ConstDecl::dump() const {
    std::string res = "ConstDecl { " +
    std::string("const") +
    bType.dump();
    for (auto iter = constDefs.begin(); iter != constDefs.end(); iter++) {
        if (std::next(iter, 1) != constDefs.end()) {
            res += iter->dump() + ", ";
        } else {
            res += iter->dump();
        }
    }
    return res + ";" +
    " }";
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

std::string ConstDef::dump() const {
    std::string res = "ConstDef { " +
    ident.dump();
    for (const auto & constExp : constExps) {
        res +=  "[" + constExp.dump() + "]";
    }
    return res + " = " +
    constInitVal.dump() +
    " }";
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

std::string ConstInitVal::dump() const {
    std::string res = "ConstInitVal { ";
    if (type == EXP) {
        res += constExp.dump();
    } else {
        res += "{";
        for (auto iter = constInitVals.begin(); iter != constInitVals.end(); iter++) {
            if (std::next(iter, 1) != constInitVals.end()) {
                res += iter->dump() + ", ";
            } else {
                res += iter->dump();
            }
        }
        res += "}";
    }
    return res + " }";
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

std::string InitVal::dump() const {
    std::string res = "InitVal { ";
    if (type == EXP) {
        res += exp.dump();
    } else {
        res += "{";
        for (auto iter = initVals.begin(); iter != initVals.end(); iter++) {
            if (std::next(iter, 1) != initVals.end()) {
                res += iter->dump() + ", ";
            } else {
                res += iter->dump();
            }
        }
        res += "}";
    }
    return res + " }";
}

/*
 * class ConstExp
 */
ConstExp::ConstExp(const AddExp &addExp) {
    this->addExp = addExp;
}

std::string ConstExp::dump() const {
    return "ConstExp { " +
    addExp.dump() +
    " }";
}

/*
 * class VarDecl
 */
VarDecl::VarDecl(const BType &bType,
                 const std::vector<VarDef> &varDefs) {
    this->bType = bType;
    this->varDefs = varDefs;
}

std::string VarDecl::dump() const {
    std::string res = "VarDecl { " +
    bType.dump();
    for (auto iter = varDefs.begin(); iter != varDefs.end(); iter++) {
        if (std::next(iter, 1) != varDefs.end()) {
            res += iter->dump() + ", ";
        } else {
            res += iter->dump();
        }
    }
    return res + " }";
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

std::string VarDef::dump() const {
    std::string res = "VarDef { " +
    ident.dump();
    for (const auto & constExp : constExps) {
        res += "[" + constExp.dump() + "]";
    }
    if (isInit) {
        res += initVal.dump();
    }
    return res + " }";
}

/*
 * FuncDef
 */
FuncDef::FuncDef(const FuncType& funcType,
                 const Ident& ident,
                 const Block& block) {
    this->funcType = funcType;
    this->ident = ident;
    this->block = block;
    hasParams = false;
}

FuncDef::FuncDef(const FuncType& funcType,
                 const Ident& ident,
                 const FuncFParams& funcFParams,
                 const Block& block) {
    this->funcType = funcType;
    this->ident = ident;
    this->funcFParams = funcFParams;
    this->block = block;
    hasParams = true;
}

std::string FuncDef::dump() const {
    return "FuncDef { " +
    funcType.dump() +
    ident.dump() +
    std::string(hasParams ? "(" + funcFParams.dump() + ")" : "") +
    block.dump() +
    " }";
}

/*
 * class FuncFParams
 */
FuncFParams::FuncFParams(const std::vector<FuncFParam>& funcFParams) {
    this->funcFParams = funcFParams;
}

std::string FuncFParams::dump() const {
    std::string res = "FuncFParams { ";
    for (auto iter = funcFParams.begin(); iter != funcFParams.end(); iter++) {
        if (std::next(iter, 1) != funcFParams.end()) {
            res += iter->dump() + ", ";
        } else {
            res += iter->dump();
        }
    }
    return res + " }";
}

/*
 * class FuncFParam
 */
FuncFParam::FuncFParam(const BType& bType,
                       const Ident& ident) {
    this->bType = bType;
    this->ident = ident;
    isArray = false;
}

FuncFParam::FuncFParam(const BType& bType,
                       const Ident& ident,
                       const std::vector<ConstExp>& constExps) {
    this->bType = bType;
    this->ident = ident;
    this->constExps = constExps;
    isArray = true;
}

std::string FuncFParam::dump() const {
    std::string res = "FuncFParam { " +
    bType.dump() +
    ident.dump();
    if (isArray) {
        for (const auto & constExp : constExps) {
            res += "[" + constExp.dump() + "]";
        }
    }
    return res + " }";
}

/*
 * class Exp
 */
Exp::Exp(const AddExp& addExp) {
    this->addExp = addExp;
}

std::string Exp::dump() const {
    return "Exp { " +
    addExp.dump() +
    " }";
}

/*
 * class FuncRParams
 */
FuncRParams::FuncRParams(const std::vector<Exp>& exps) {
    this->exps = exps;
}

std::string FuncRParams::dump() const {
    std::string res = "FuncRParams { ";
    for (auto iter = exps.begin(); iter != exps.end(); iter++) {
        if (std::next(iter, 1) != exps.end()) {
            res += iter->dump() + ", ";
        } else {
            res += iter->dump();
        }
    }
    return res + " }";
}

/*
 * class LVal
 */
LVal::LVal(const Ident &ident,
           const std::vector<Exp> &exps) {
    this->ident = ident;
    this->exps = exps;
}

std::string LVal::dump() const {
    std::string res = "LVal { " +
    ident.dump();
    for (const auto & exp : exps) {
        res += "[" + exp.dump() + "]";
    }
    return res + " }";
}

/*
 * class PrimaryExp
 */
PrimaryExp::PrimaryExp(const Exp& exp) {
    this->exp = exp;
    type = EXP;
}

PrimaryExp::PrimaryExp(const LVal& lVal) {
    this->lVal = lVal;
    type = LVAL;
}

PrimaryExp::PrimaryExp(const Number& number) {
    this->number = number;
    type = NUM;
}

std::string PrimaryExp::dump() const {
    std::string res = "PrimaryExp { ";
    switch (type) {
        case EXP:
            res += "(" + exp.dump() + ")";
            break;
        case LVAL:
            res += lVal.dump();
            break;
        case NUM:
            res += number.dump();
            break;
    }
    return res + " }";
}

/*
 * class UnaryExp
 */
UnaryExp::UnaryExp(const PrimaryExp& primaryExp) {
    this->primaryExp = primaryExp;
    type = PRI;
}

UnaryExp::UnaryExp(const Ident &ident) {
    this->ident = ident;
    hasParams = false;
    type = IDE;
}

UnaryExp::UnaryExp(const Ident& ident,
                   const FuncRParams& funcRParams) {
    this->ident = ident;
    this->funcRParams = funcRParams;
    hasParams = true;
    type = IDE;
}

UnaryExp::UnaryExp(const UnaryOp& unaryOp,
                   UnaryExp unaryExp) {
    this->unaryOp = unaryOp;
    this->unaryExp = &unaryExp;
    type = UNA;
}

std::string UnaryExp::dump() const {
    std::string res = "UnaryExp { ";
    switch (type) {
        case PRI:
            res += primaryExp.dump();
            break;
        case IDE:
            res += ident.dump();
            if (hasParams) {
                res += funcRParams.dump();
            }
            break;
        case UNA:
            res += unaryOp.dump() + unaryExp->dump();
            break;
    }
    return res + " }";
}

/*
 * class MulExp
 */
MulExp::MulExp(const std::vector<UnaryExp>& unaryExps,
               const std::vector<Token>& ops) {
    this->unaryExps = unaryExps;
    this->ops = ops;
}

std::string MulExp::dump() const {
    std::string res = "MulExp { ";
    for (auto i = 0; i < unaryExps.size() - 1; i++) {
        res += unaryExps[i].dump() + " ";
        res += ops[i].getTokenString() + " ";
    }
    return res + unaryExps[unaryExps.size() - 1].dump();
}

/*
 * class AddExp
 */
AddExp::AddExp(const std::vector<MulExp>& mulExps,
               const std::vector<Token>& ops) {
    this->mulExps = mulExps;
    this->ops = ops;
}

std::string AddExp::dump() const {
    std::string res = "AddExp { ";
    for (auto i = 0; i < mulExps.size() - 1; i++) {
        res += mulExps[i].dump() + " ";
        res += ops[i].getTokenString() + " ";
    }
    return res + mulExps[mulExps.size() - 1].dump();
}

/*
 * class RelExp
 */
RelExp::RelExp(const std::vector<AddExp>& addExps,
               const std::vector<Token>& ops) {
    this->addExps = addExps;
    this->ops = ops;
}

std::string RelExp::dump() const {
    std::string res = "RelExp { ";
    for (auto i = 0; i < addExps.size() - 1; i++) {
        res += addExps[i].dump() + " ";
        res += ops[i].getTokenString() + " ";
    }
    return res + addExps[addExps.size() - 1].dump();
}

/*
 * class EqExp
 */
EqExp::EqExp(const std::vector<RelExp>& relExps,
             const std::vector<Token>& ops) {
    this->relExps = relExps;
    this->ops = ops;
}

std::string EqExp::dump() const {
    std::string res = "EqExp { ";
    for (auto i = 0; i < relExps.size() - 1; i++) {
        res += relExps[i].dump() + " ";
        res += ops[i].getTokenString() + " ";
    }
    return res + relExps[relExps.size() - 1].dump();
}

/*
 * class LAndExp
 */
LAndExp::LAndExp(const std::vector<EqExp>& eqExps,
                 const std::vector<Token>& ops) {
    this->eqExps = eqExps;
    this->ops = ops;
}

std::string LAndExp::dump() const {
    std::string res = "LAndExp { ";
    for (auto i = 0; i < eqExps.size() - 1; i++) {
        res += eqExps[i].dump() + " ";
        res += ops[i].getTokenString() + " ";
    }
    return res + eqExps[eqExps.size() - 1].dump();
}

/*
 * class LOrExp
 */
LOrExp::LOrExp(const std::vector<LAndExp>& lAndExps,
                const std::vector<Token>& ops) {
    this->lAndExps = lAndExps;
    this->ops = ops;
}

std::string LOrExp::dump() const {
    std::string res = "LOrExp { ";
    for (auto i = 0; i < lAndExps.size() - 1; i++) {
        res += lAndExps[i].dump() + " ";
        res += ops[i].getTokenString() + " ";
    }
    return res + lAndExps[lAndExps.size() - 1].dump();
}
