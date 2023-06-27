//
// Created by 11678 on 2023/6/26.
//
#include "Token.h"

Token::Token(const std::string& sym, const std::string& str, int lin) {
    tokenSymbol = sym;
    tokenString = str;
    tokenLineNumber = lin;
}

std::string Token::getTokenSymbol() {
    return tokenSymbol;
}

std::string Token::getTokenString() {
    return tokenString;
}

int Token::getTokenLineNumber() const {
    return tokenLineNumber;
}

Token::Token() = default;

Token::~Token() = default;

std::ostream& operator<<(const std::ostream& os, Token token) {
    std::cout << token.getTokenSymbol() << ": ";
    std::cout << token.getTokenString();
    return const_cast<std::ostream &>(os);
}

