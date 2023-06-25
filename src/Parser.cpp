//
// Created by Hibiki33 on 2023/6/24.
//

#include "Parser.h"

Parser::Parser(std::vector<Token> tokens) {
    tokenList.assign(tokens.begin(), tokens.end());
}

Parser::~Parser() = default;
