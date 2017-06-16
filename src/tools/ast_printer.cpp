#include "../Expr.hpp"
#include "../scanner/token.hpp"
#include <iostream>
#include <memory>
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
            std::cout << "nil";
        std::cout << expr->value;
    }
    void visitUnaryExpr(UnaryExpr* expr) override {
        return parenthesize(expr->Operator.lexeme, {expr->right});
    }
    void parenthesize(std::string name, std::vector<Expr*> exprs) {
        std::string pp = "(" + name + " ";
        // print
        std::cout << pp;
        for (auto expr : exprs) {
            expr->accept(this);
        }
	std::cout << ") ";
    }
};

int main() {
    std::unique_ptr<Expr> rootExpr(
        new BinaryExpr(new UnaryExpr(*new Token(TokenType::MINUS, "-", "", 1),
                                     new LiteralExpr("123")),
                       *new Token(TokenType::STAR, "*", "", 1),
                       new GroupingExpr(new LiteralExpr("45.67"))));
    ASTPrinter pp;
    pp.print(rootExpr.get());
    std::cout << std::endl;
    return 0;
}
