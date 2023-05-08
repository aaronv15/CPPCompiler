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
    NumberExprNode(double value) : value_(value) {}

private:
    double value_;
};

class BinaryExprNode : public ExprNode {
public:
    BinaryExprNode(TokenType op, std::unique_ptr<ExprNode> lhs, std::unique_ptr<ExprNode> rhs)
        : op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

private:
    TokenType op_;
    std::unique_ptr<ExprNode> lhs_;
    std::unique_ptr<ExprNode> rhs_;
};

class Parser {
public:
    explicit Parser(Lexer& lexer) : lexer_(lexer), currentToken_(lexer.getNextToken()) {}

    std::unique_ptr<ExprNode> parse();

private:
    Lexer& lexer_;
    Token currentToken_;

    std::unique_ptr<ExprNode> parseExpression() {
        // Implement expression parsing
    }

    std::unique_ptr<ExprNode> parsePrimary() {
        // Implement primary expression parsing
    }

    std::unique_ptr<ExprNode> parseBinary(int precedence) {
        // Implement binary expression parsing
    }
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