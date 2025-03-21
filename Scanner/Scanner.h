
#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../Tokens/TokenType.h"
#include "../Tokens/Token.h"

namespace cloven {
    class Scanner {
    public:
        explicit Scanner(const std::string& source);
        std::vector<Token> scanTokens();
    private:
        const std::unordered_map<std::string, TokenType> keywords;
        std::string source;
        std::vector<Token> tokens;
        int start;
        int current;
        int line;

        [[nodiscard]] bool isAtEnd() const;
        void scanToken();
        char advance();
        void addToken(TokenType type);
        void addToken(TokenType type, const std::any& literal);
        bool match(char expected);
        [[nodiscard]] char peek() const;
        void string();
        static bool isDigit(char c);
        void number();
        [[nodiscard]] char peekNext() const;
        void identifier();
        static bool isAlpha(char c);
        static bool isAlphaNumeric(char c);
    };
}

#endif // SCANNER_H
