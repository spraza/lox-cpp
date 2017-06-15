#include "../Expr.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace lox;

class ASTPrinter : public ExprVisitor {
  public:
    void print(Expr* expr) { return expr->accept(this); }
    void visitBinaryExpr(BinaryExpr* expr) override {
        return parenthesize(expr->Operator.lexeme, {expr->left, expr->right});
    }
    void visitGroupingExpr(GroupingExpr* expr) override {
        return parenthesize("group", {expr->expression});
    }
    void visitLiteralExpr(LiteralExpr* expr) override {
        if (expr->value.empty())
            return "nil";
        std::cout << expr->value;
    }
    void visitUnaryExpr(UnaryExpr* expr) override {
        return parenthesize(expr->Operator.lexeme, {expr->right});
    }
    void parenthesize(std::string name, std::vector<Expr*> exprs) {
        std::string pp = "(" + name;
        for (auto expr : exprs) {
            pp += " ";
            pp += expr->accept(this);
        }
        pp += ")";
        // print
        std::cout << pp << std::endl;
    }
};
