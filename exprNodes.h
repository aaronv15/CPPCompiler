#ifndef EXPRNODE_H
#define EXPRNODE_H

#include <iostream>
#include <memory>
#include "lexer.h"

class ExprNode {
public:
    virtual ~ExprNode() = default;
};

class NumberExprNode : public ExprNode {
public:
    explicit NumberExprNode(double value) : value_(value) {}
    double getValue() const { return value_; }
private:
    double value_;
};

class VariableExprNode : public ExprNode {
public:
    VariableExprNode(const std::string& name) : name_(name) {}

private:
    std::string name_;
};

class BinaryExprNode : public ExprNode {
public:
    BinaryExprNode(TokenType op, std::unique_ptr<ExprNode> lhs, std::unique_ptr<ExprNode> rhs)
        : op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    TokenType getOperator() const { return op_; }
    const ExprNode* getLeft() const { return lhs_.get(); }
    const ExprNode* getRight() const { return rhs_.get(); }

private:
    TokenType op_;
    std::unique_ptr<ExprNode> lhs_;
    std::unique_ptr<ExprNode> rhs_;
};

class StatementNode : public ExprNode {
};

#endif