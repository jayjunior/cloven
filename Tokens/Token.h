#pragma once
#ifndef TOKEN_H
#define TOKEN_H

#include <any>
#include <string>
#include "TokenType.h"

namespace cloven {
    class Token {
    public:
        Token(const TokenType& type, const std::string& lexeme, int line, const std::any& literal);

        friend std::ostream& operator<<(std::ostream& os, const Token& token);

    private:
        TokenType type;
        std::string lexeme;
        int line;
        std::any literal;
    };
}

#endif // TOKEN_H

