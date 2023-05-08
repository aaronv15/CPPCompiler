//g++ -c ast.cpp

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

#pragma region testLexer
// int main()
// {
//     std::string input = "if else for foo + 42 - bar(123) + asdf[96 - 3] * \"24";
//     Lexer lexer(input);

//     Token token;
//     do
//     {
//         token = lexer.getNextToken();
//         std::cout << "Type: " << static_cast<int>(token.type) << ", Value: " << token.value << std::endl;
//     } while (token.type != TokenType::END_OF_FILE);

//     return 0;
// }
#pragma endregion

// g++ -o ast lexer.o ast.o