#include <iostream>
#include <memory>
#include "lexer.h"
#include "exprNodes.h"

class Parser
{
public:
    explicit Parser(Lexer &lexer) : lexer_(lexer), currentToken_(lexer.getNextToken()) {}

    std::unique_ptr<ExprNode> parse();

private:
    Lexer &lexer_;
    Token currentToken_;

    std::unique_ptr<NumberExprNode> parseNumber();
    std::unique_ptr<ExprNode> Parser::parseExpression();
};

std::unique_ptr<ExprNode> Parser::parse()
{
    if (
        currentToken_.type == TokenType::OPERATOR_ADD ||
        currentToken_.type == TokenType::OPERATOR_SUBTRACT ||
        currentToken_.type == TokenType::OPERATOR_MULTIPLY ||
        currentToken_.type == TokenType::OPERATOR_DIVIDE)
    {
        return parseExpression();
    }
    // Add more top-level constructs as needed

    // If the parser reaches this point, there's a syntax error
    throw std::runtime_error("Unexpected token: " + currentToken_.value);
}

std::unique_ptr<NumberExprNode> Parser::parseNumber()
{
    double value = std::stod(currentToken_.value);
    currentToken_ = lexer_.getNextToken();
    return std::make_unique<NumberExprNode>(value);
}

std::unique_ptr<ExprNode> Parser::parseExpression()
{
    std::unique_ptr<ExprNode> lhs = parseNumber();

    while (
        currentToken_.type == TokenType::OPERATOR_ADD ||
        currentToken_.type == TokenType::OPERATOR_SUBTRACT ||
        currentToken_.type == TokenType::OPERATOR_MULTIPLY ||
        currentToken_.type == TokenType::OPERATOR_DIVIDE)
    {
        TokenType op = currentToken_.type;
        currentToken_ = lexer_.getNextToken();
        std::unique_ptr<ExprNode> rhs = parseNumber();
        lhs = std::make_unique<BinaryExprNode>(op, std::move(lhs), std::move(rhs));
    }

    return lhs;
}
