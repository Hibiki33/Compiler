//
// Created by Hibiki33 on 2023/6/24.
//

#include "Parser.h"

using namespace Front;

Parser::Parser(const std::vector<Token>& tokens) {
    this->tokens = tokens;
    index = 0;
}

Parser::~Parser() = default;

bool Parser::syntacticAnalyze() {
    entry = Ast(parseCompUnit());
    return index == tokens.size();
}

CompUnit Parser::parseCompUnit() {
    std::vector<Decl> decls;
    std::vector<FuncDef> funcDefs;
    MainFuncDef mainFuncDef;

    while (getSymbol(2) != "LPARENT") {
        decls.push_back(parseDecl());
    }

    while (getSymbol(1) != "MAINTK") {
        funcDefs.push_back(parseFuncDef());
    }

    mainFuncDef = parseMainFuncDef();

    return CompUnit(decls, funcDefs, mainFuncDef);
}

Decl Parser::parseDecl() {
    if (getSymbol(0) == "CONSTTK") {
        return Decl(parseConstDecl());
    }
    return Decl(parseVarDecl());
}

ConstDecl Parser::parseConstDecl() {
}
BType Parser::parseBType() {
}
ConstDef Parser::parseConstDef(){
}
ConstInitVal Parser::parseConstInitVal(){
}
VarDecl Parser::parseVarDecl(){
}
VarDef Parser::parseVarDef(){
}
InitVal Parser::parseInitVal(){
}
FuncDef Parser::parseFuncDef(){
}
MainFuncDef Parser::parseMainFuncDef() {
}
FuncType Parser::parseFuncType(){
}
FuncFParams Parser::parseFuncFParams(){
}
FuncFParam Parser::parseFuncFParam(){
}
Block Parser::parseBlock(){
}
BlockItem Parser::parseBlockItem(){
}
Stmt Parser::parseStmt(){
}
Exp Parser::parseExp(){
}
Cond Parser::parseCond(){
}
LVal Parser::parseLVal(){
}
PrimaryExp Parser::parsePrimaryExp(){
}
Number Parser::parseNumber(){
}
UnaryExp Parser::parseUnaryExp(){
}
FuncRParams Parser::parseFuncRParams(){
}
MulExp Parser::parseMulExp(){
}
AddExp Parser::parseAddExp(){
}
RelExp Parser::parseRelExp(){
}
EqExp Parser::parseEqExp(){
}
LAndExp Parser::parseLAndExp(){
}
LOrExp Parser::parseLOrExp(){
}
ConstExp Parser::parseConstExp(){
}
IntConst Parser::parseIntConst(){
}
Ident Parser::parseIdent(){
}
FormatString Parser::parseFormatString(){
}
UnaryOp Parser::parseUnaryOp(){
}

std::string Parser::getSymbol(int bias) {
    return tokens[index + bias].getTokenSymbol();
}

std::string Parser::getString(int bias) {
    return tokens[index + bias].getTokenString();
}







