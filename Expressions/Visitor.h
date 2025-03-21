// Visitor.h
#ifndef VISITOR_H
#define VISITOR_H
#include "Expr.h"

namespace cloven {

    class Visitor {
    public:
        virtual ~Visitor() = default;

        virtual void visitBinary(Expr::Binary binary) = 0;
        virtual void visitGrouping(Expr::Grouping&grouping) = 0;
        virtual void visitLiteral(Expr::Literal literal) = 0;
        virtual void visitUnary(Expr::Unary unary) = 0;
    };
}

#endif // VISITOR_H