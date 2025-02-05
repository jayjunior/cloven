

#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include "Token.h"
#include "Cloven.h"
namespace  cloven {
    class Scanner {
    public:
        explicit Scanner(const std::string& source) {
            this->source = source;
        }
        std::vector<Token> scanTokens() {
            while (!isAtEnd()) {
                start = current;
                scanToken();
            }
            return tokens;
        }
    private:
        const std::unordered_map<std::string, TokenType> keywords = {
            {"and",AND},
            {"class",CLASS},
            {"else",ELSE},
            {"false",FALSE},
            {"fun",FUN},
            {"for",FOR},
            {"if",IF},
            {"nil",NIL},
            {"or",OR},
            {"print",PRINT},
            {"return",RETURN},
            {"super",SUPER},
            {"this",THIS},
            {"true",TRUE},
            {"var",VAR},
            {"while",WHILE},
        };
        std::string source;
        std::vector<Token> tokens;
        int start = 0;
        int current = 0;
        int line = 1;

        [[nodiscard]] bool isAtEnd() const {
            return current >= source.length();
        }

        void scanToken() {
            switch (char c = advance()) {
                case '(': addToken(LEFT_PAREN); break;
                case ')': addToken(RIGHT_PAREN); break;
                case '{': addToken(LEFT_BRACE); break;
                case '}': addToken(RIGHT_BRACE); break;
                case ',': addToken(COMMA); break;
                case '.': addToken(DOT); break;
                case '-': addToken(MINUS); break;
                case '+': addToken(PLUS); break;
                case ';': addToken(SEMICOLON); break;
                case '*': addToken(STAR); break;
                case '!': addToken(match('=') ? BANG_EQUAL : BANG); break;
                case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;
                case '<': addToken(match('=') ? LESS_EQUAL : LESS); break;
                case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;
                case '/':
                    if (match('/')) {
                        while (peek() != '\n' && !isAtEnd()) advance();
                    } else {
                        addToken(SLASH);
                    }
                    break;
                case ' ':
                case '\r':
                case '\t':
                    break;
                case '\n':
                    line++;
                    break;
                case '"': string(); break;
                case 'o':
                    if (peek() == 'r') {
                        addToken(OR);
                    }
                    break;
                default: {
                    if (isDigit(c)) {
                        number();
                    }else if (isAlpha(c)) {
                        identifier();
                    }
                    else {
                        Cloven::error(line, "Unexpected character.");
                    }
                    Cloven::error(line, "Unexpected character.");
                    break;
                }

            }
        }

        char advance() {
            current++;
            return source.at(current - 1);
        }

        void addToken(TokenType type) {
            addToken(type, nullptr);
        }

        void addToken(TokenType type , const std::any& literal) {
            std::string text = source.substr(start,current);
            tokens.emplace_back(type,text,line,literal);
        }

        bool match(const char expected) {
            if (isAtEnd()) return false;
            if (source.at(current) != expected) return false;
            current ++;
            return true;
        }

        [[nodiscard]] char peek() const {
            if (isAtEnd()) return '\0';
            return source.at(current);
        }

        void string() {
            while (peek() != '"' && !isAtEnd()) {
                if (peek() == '\n') line++;
                advance();
            }
            if (isAtEnd()) {
                Cloven::error(line, "Unterminated string.");
                return;
            }
            advance();
            std::string value = source.substr(start + 1, current - 1);
            addToken(STRING, value);
        }

        static bool isDigit(const char c) {
            return c >= '0' && c <= '9';
        }

        void number() {
            while (isDigit(peek())) advance();

            if (peek() == '.' && isDigit(peekNext())) {
                advance();
                while (isDigit(peek())) advance();
            }
            addToken(NUMBER, std::stod(source.substr(start, current)));
        }

        [[nodiscard]] char  peekNext() const {
            if (current + 1 >= source.length()) return '\0';
            return source.at(current + 1);
        }

        void identifier() {
            while (isAlphaNumeric(peek())) advance();
            const std::string text = source.substr(start, current);
            TokenType type = keywords.at(text);
            if (type == NULL) type = IDENTIFIER;
            addToken(type);
        }

        static bool isAlpha(const char c) {
            return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
        }

        static bool isAlphaNumeric(const char c) {
            return isAlpha(c) || isDigit(c);
        }

    };
}


#endif // SCANNER_H


