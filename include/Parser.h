//
// Created by Hibiki33 on 2023/6/24.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"


class Parser {
public:
    explicit Parser(std::vector<Token> tokens);

    ~Parser();

private:
    std::vector<Token> tokenList;

};


#endif //COMPILER_PARSER_H
