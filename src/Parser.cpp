//
// Created by Hibiki33 on 2023/6/24.
//

#include "Parser.h"

using namespace Front;

Parser::Parser(const std::vector<Token>& tokenList) : tokenList(tokenList) {}

Parser::~Parser() = default;

CompUnit Parser::parseCompUnit() {
    std::vector<Decl> decls;
    std::vector<FuncDef> funcDefs;
    MainFuncDef mainFuncDef;




    return CompUnit(decls, funcDefs, mainFuncDef);
}

Decl Parser::parseDecl(){
}
ConstDecl Parser::parseConstDecl(){
}
BType Parser::parseBType(){
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



