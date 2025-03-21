#ifndef Expr_H
#define Expr_H

#include <string>
#include <vector>
#include "../Tokens/Token.h"
#include "Visitor.h"
using string = std::string;

namespace cloven {
    class Visitor;

    class Expr {
    public:
        Expr() = default;

        class Binary {
        public:
            Expr& left;
            Token& op;
            Expr& right;
            Binary(Expr& left,Token& op,Expr& right) :
                left(left),
                op(op),
                right(right)
            {}
            void accept(Visitor& visitor) {
                visitor.visitBinary(*this);
            }
        };

        class Grouping {
        public:
            Expr& expression;
            explicit Grouping(Expr& expression) :
                expression(expression)
            {}
            void accept(Visitor& visitor) {
                visitor.visitGrouping(*this);
            }
        };

        class Literal {
        public:
            string& value;
            explicit Literal(string& value) :
                value(value)
            {}
            void accept(Visitor& visitor) {
                visitor.visitLiteral(*this);
            }
        };

        class Unary {
        public:
            Token& op;
            Expr& right;
            Unary(Token& op,Expr& right) :
                op(op),
                right(right)
            {}
            void accept(Visitor& visitor) {
                visitor.visitUnary(*this);
            }
        };

    };
}

#endif //Expr_H
