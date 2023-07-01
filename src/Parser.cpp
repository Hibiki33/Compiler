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

// CompUnit ->  {Decl} {FuncDef} MainFuncDef
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

// Decl -> ConstDecl | VarDecl;
Decl Parser::parseDecl() {
    if (getSymbol(0) == "CONSTTK") {
        return Decl(parseConstDecl());
    }
    return Decl(parseVarDecl());
}

// ConstDecl -> 'const' BType ConstDef { ',' ConstDef } ';'
ConstDecl Parser::parseConstDecl() {
    BType bType;
    std::vector<ConstDef> constDefs;

    if (getSymbol(0) != "CONSTTK") {
        // TODO: HANDLE ERROR
    }
    index += 1;

    bType = parseBType();

    // one 'ConstDef' at least
    constDefs.push_back(parseConstDef());
    while (getSymbol(0) == "COMMA") {
        index += 1;
        constDefs.push_back(parseConstDef());
    }

    if (getSymbol(0) != "SEMICN") {
        // TODO: HANDLE ERROR
    }
    index += 1;

    return ConstDecl(bType, constDefs);
}

// BType -> 'int'
BType Parser::parseBType() {
    if (getSymbol(0) != "INTTK") {
        // TODO: HANDLE ERROR
    }
    index += 1;
    return BType(BType::Type::INT);
}

// ConstDef -> Ident { '[' ConstExp ']' } '=' ConstInitVal
ConstDef Parser::parseConstDef(){
    Ident ident;
    std::vector<ConstExp> constExps;
    ConstInitVal constInitVal;

    if (getSymbol(0) != "IDENFR") {
        // TODO: HANDLE ERROR
    }
    ident = parseIdent();

    while (getSymbol(0) == "LBRACK") {
        index += 1;
        constExps.push_back(parseConstExp());
        if (getSymbol(0) != "RBRACK") {
            // TODO: HANDLE ERROR
        }
        index += 1;
    }

    if (getSymbol(0) != "ASSIGN") {
        // TODO: HANDLE ERROR
    }
    index += 1;

    constInitVal = parseConstInitVal();

    return ConstDef(ident, constExps, constInitVal);
}

// ConstInitVal -> ConstExp
//              | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
ConstInitVal Parser::parseConstInitVal() {
    if (getSymbol(0) == "LBRACE") {
        index += 1;

        std::vector<ConstInitVal> constInitVals;
        while (getSymbol(0) != "RBRACE") {
            constInitVals.push_back(parseConstInitVal());
            if (getSymbol(0) == "COMMA") {
                index += 1;
            }
        }
        index += 1;

        return ConstInitVal(constInitVals);
    }

    return ConstInitVal(parseConstExp());
}

// VarDecl -> BType VarDef { ',' VarDef } ';'
VarDecl Parser::parseVarDecl() {
    BType bType;
    std::vector<VarDef> varDefs;

    bType = parseBType();

    // one 'VarDef' at least
    varDefs.push_back(parseVarDef());
    while (getSymbol(0) == "COMMA") {
        index += 1;
        varDefs.push_back(parseVarDef());
    }

    if (getSymbol(0) != "SEMICN") {
        // TODO: HANDLE ERROR
    }
    index += 1;

    return VarDecl(bType, varDefs);
}

// VarDef -> Ident { '[' ConstExp ']' }
//         | Ident { '[' ConstExp ']' } '=' InitVal
VarDef Parser::parseVarDef() {
    Ident ident;
    std::vector<ConstExp> constExps;

    ident = parseIdent();

    while (getSymbol(0) == "LBRACK") {
        index += 1;
        constExps.push_back(parseConstExp());
        if (getSymbol(0) != "RBRACK") {
            // TODO: HANDLE ERROR
        }
        index += 1;
    }

    if (getSymbol(0) == "ASSIGN") {
        index += 1;
        InitVal initVal = parseInitVal();
        return VarDef(ident, constExps, initVal);
    }

    return VarDef(ident, constExps);
}

// InitVal -> Exp | '{' [ InitVal { ',' InitVal } ] '}'
InitVal Parser::parseInitVal() {
    if (getSymbol(0) == "LBRACE") {
        index += 1;

        std::vector<InitVal> initVals;
        while (getSymbol(0) != "RBRACE") {
            initVals.push_back(parseInitVal());
            if (getSymbol(0) == "COMMA") {
                index += 1;
            }
        }
        index += 1;

        return InitVal(initVals);
    }

    return InitVal(parseExp());
}

// FuncDef -> FuncType Ident '(' [FuncFParams] ')' Block
FuncDef Parser::parseFuncDef() {
    FuncType funcType;
    Ident ident;
    FuncFParams funcFParams;
    Block block;

    funcType = parseFuncType();

    ident = parseIdent();

    if (getSymbol(0) != "LPARENT") {
        // TODO: HANDLE ERROR
    }
    funcFParams = parseFuncFParams();
    if (getSymbol(0) != "RPARENT") {
        // TODO: HANDLE ERROR
    }

    block = parseBlock();

    return FuncDef(funcType, ident, funcFParams, block);
}

// MainFuncDef -> 'int' 'main' '(' ')' Block
MainFuncDef Parser::parseMainFuncDef() {
    if (getSymbol(0) != "INTTK") {
        // TODO: HANDLE ERROR
    }
    index += 1;

    if (getSymbol(0) != "MAINTK") {
        // TODO: HANDLE ERROR
    }
    index += 1;

    if (getSymbol(0) != "LPARENT") {
        // TODO: HANDLE ERROR
    }
    index += 1;

    if (getSymbol(0) != "RPARENT") {
        // TODO: HANDLE ERROR
    }
    index += 1;

    return MainFuncDef(parseBlock());
}

// FuncType -> 'void' | 'int'
FuncType Parser::parseFuncType() {
    if (getSymbol(0) == "VOIDTK") {
        return FuncType(FuncType::Type::VOID);
    }

    return FuncType(FuncType::Type::INT);
}

// FuncFParams -> FuncFParam { ',' FuncFParam }
FuncFParams Parser::parseFuncFParams() {
    std::vector<FuncFParam> funcFParams;

    // one 'FuncFParam' at least
    funcFParams.push_back(parseFuncFParam());
    while (getSymbol(0) == "COMMA") {
        index += 1;
        funcFParams.push_back(parseFuncFParam());
    }

    return FuncFParams(funcFParams);
}

// FuncFParam -> BType Ident ['[' ']' { '[' ConstExp ']' }]
FuncFParam Parser::parseFuncFParam() {
    BType bType;
    Ident ident;
    std::vector<ConstExp> constExps;
    int dimension = 0;

    bType = parseBType();
    ident = parseIdent();

    if (getSymbol(0) == "LBRACK") {
        if (getSymbol(1) != "RBRACK") {
            // TODO: HANDLE ERROR
        }
        index += 2;
        dimension += 1;

        while (getSymbol(0) == "LBRACK") {
            index += 1;
            constExps.push_back(parseConstExp());
            if (getSymbol(0) != "RBRACK") {
                // TODO: HANDLE ERROR
            }
            index += 1;
            dimension += 1;
        }
    }

    return FuncFParam(bType, ident, constExps, dimension);
}

// Block → '{' { BlockItem } '}'
Block Parser::parseBlock() {
    std::vector<BlockItem> blockItems;

    if (getSymbol(0) != "LBRACE") {
        // TODO:
    }
    index += 1;

    while (getSymbol(0) != "RBRACE") {
        blockItems.push_back(parseBlockItem());
    }
    index += 1;

    return Block(blockItems);
}

// BlockItem -> Decl | Stmt
BlockItem Parser::parseBlockItem() {
    if (getSymbol(0) == "CONSTTK" || getSymbol(0) == "INTTK") {
        return BlockItem(parseDecl());
    }
    return BlockItem(parseStmt());
}

// Stmt -> LVal '=' Exp ';'
//      | [Exp] ';'
//      | Block
//      | 'if' '(' Cond ')' Stmt [ 'else' Stmt ]
//      | 'while' '(' Cond ')' Stmt
//      | 'break' ';' | 'continue' ';'
//      | 'return' [Exp] ';'
//      | LVal '=' 'getint''('')'';'
//      | 'printf''('FormatString{','Exp}')'';'
Stmt Parser::parseStmt() {

}

// Exp -> AddExp
Exp Parser::parseExp() {
    return Exp(parseAddExp());
}

// Cond -> LOrExp
Cond Parser::parseCond() {
    return Cond(parseLOrExp());
}

// LVal -> Ident {'[' Exp ']'}
LVal Parser::parseLVal(){
    Ident ident;
    std::vector<Exp> exps;

    ident = parseIdent();

    if (getSymbol(0) != "LBRACK") {
        // TODO:
    }
    index += 1;

    while (getSymbol(0) != "RBRACK") {
        exps.push_back(parseExp());
    }
    index += 1;

    return LVal(ident, exps);
}

// PrimaryExp -> '(' Exp ')' | LVal | Number
PrimaryExp Parser::parsePrimaryExp() {
    if (getSymbol(0) == "LPARENT") {
        index += 1;
        Exp exp = parseExp();
        if (getSymbol(0) != "RPARENT") {
            // TODO:
        }
        index += 1;
    } else if (getSymbol(0) == "INTCON") {
        return PrimaryExp(parseNumber());
    }

    return PrimaryExp(parseLVal());
}

// Number -> IntConst
Number Parser::parseNumber() {
    return Number(parseIntConst());
}

// UnaryExp -> PrimaryExp
//           | Ident '(' [FuncRParams] ')'
//           | UnaryOp UnaryExp
UnaryExp Parser::parseUnaryExp() {
    // in case of 'LVal' in 'Primary', whose first token is 'Ident'
    if (getSymbol(0) == "IDENFR" && getSymbol(1) == "LPARENT") {
        Ident ident = parseIdent();
        // for "LPARENT"
        index += 1;

        if (getSymbol(0) == "RPARENT") {
            index += 1;
            return UnaryExp(ident);
        } else {
            FuncRParams funcRParams = parseFuncRParams();
            if (getSymbol(0) != "RPARENT") {
                // TODO:
            }
            index += 1;

            return UnaryExp(ident, funcRParams);
        }
    } else if (getSymbol(0) == "PLUS" ||
               getSymbol(0) == "MINU" ||
               getSymbol(0) == "NOT") {
        UnaryOp unaryOp = parseUnaryOp();
        UnaryExp unaryExp = parseUnaryExp();
        // TODO: Check whether it is correct!
        return UnaryExp(unaryOp, &unaryExp);
    }

    return UnaryExp(parsePrimaryExp());
}

// FuncRParams -> Exp { ',' Exp }
FuncRParams Parser::parseFuncRParams() {
    std::vector<Exp> exps;

    // one 'Exp' at least
    exps.push_back(parseExp());
    while (getSymbol(0) == "COMMA") {
        index += 1;
        exps.push_back(parseExp());
    }

    return FuncRParams(exps);
}

// MulExp -> UnaryExp { ('*' | '/' | '%') UnaryExp }
MulExp Parser::parseMulExp() {
    std::vector<UnaryExp> unaryExps;
    std::vector<Token> ops;

    unaryExps.push_back(parseUnaryExp());
    while (getSymbol(0) == "MULT" ||
           getSymbol(0) == "DIV" ||
           getSymbol(0) == "MOD") {
        ops.push_back(getToken(0));
        index += 1;

        unaryExps.push_back(parseUnaryExp());
    }

    return MulExp(unaryExps, ops);
}

// AddExp -> MulExp { ('+' | '-') MulExp }
AddExp Parser::parseAddExp() {
    std::vector<MulExp> mulExps;
    std::vector<Token> ops;

    mulExps.push_back(parseMulExp());
    while (getSymbol(0) == "PLUS" ||
           getSymbol(0) == "MINU") {
        ops.push_back(getToken(0));
        index += 1;

        mulExps.push_back(parseMulExp());
    }

    return AddExp(mulExps, ops);
}

// RelExp -> AddExp { ('<' | '>' | '<=' | '>=') AddExp }
RelExp Parser::parseRelExp() {
    std::vector<AddExp> addExps;
    std::vector<Token> ops;

    addExps.push_back(parseAddExp());
    while (getSymbol(0) == "LSS" ||
           getSymbol(0) == "LEQ" ||
           getSymbol(0) == "GRE" ||
           getSymbol(0) == "GEQ") {
        ops.push_back(getToken(0));
        index += 1;

        addExps.push_back(parseAddExp());
    }

    return RelExp(addExps, ops);
}

// EqExp -> RelExp { ('==' | '!=') RelExp }
EqExp Parser::parseEqExp() {
    std::vector<RelExp> relExps;
    std::vector<Token> ops;

    relExps.push_back(parseRelExp());
    while (getSymbol(0) == "EQL" ||
           getSymbol(0) == "NEQ") {
        ops.push_back(getToken(0));
        index += 1;

        relExps.push_back(parseRelExp());
    }

    return EqExp(relExps, ops);
}

// LAndExp -> EqExp { '&&' EqExp }
LAndExp Parser::parseLAndExp() {
    std::vector<EqExp> eqExps;
    std::vector<Token> ops;

    eqExps.push_back(parseEqExp());
    while (getSymbol(0) == "AND") {
        ops.push_back(getToken(0));
        index += 1;

        eqExps.push_back(parseEqExp());
    }

    return LAndExp(eqExps, ops);
}

LOrExp Parser::parseLOrExp() {
    std::vector<LAndExp> lAndExps;
    std::vector<Token> ops;

    lAndExps.push_back(parseLAndExp());
    while (getSymbol(0) == "OR") {
        ops.push_back(getToken(0));
        index += 1;

        lAndExps.push_back(parseLAndExp());
    }

    return LOrExp(lAndExps, ops);
}

ConstExp Parser::parseConstExp() {

}

// IntConst
IntConst Parser::parseIntConst() {
    Token token = getToken(0);
    index += 1;

    return IntConst(token);
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

Token Parser::getToken(int bias) {
    return tokens[index + bias];
}







