//g++ -c lexer.cpp

#include <iostream>
#include <memory>

enum class TokenType
{
    INTEGER,
    FLOAT,
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_ELF,
    KEYWORD_DO,
    KEYWORD_FOR,
    KEYWORD_WHILE,
    KEYWORD_BOOLEAN,
    KEYWORD_TRUE,
    KEYWORD_FALSE,
    KEYWORD_INTEGER,
    KEYWORD_FLOAT,
    KEYWORD_DOUBLE,
    KEYWORD_CHAR,
    KEYWORD_STRING,
    KEYWORD_STR,
    OPERATOR_ADD,
    OPERATOR_SUBTRACT,
    OPERATOR_MULTIPLY,
    OPERATOR_DIVIDE,
    QUOTE,
    OPEN_PAREN,
    CLOSE_PAREN,
    OPEN_CURL,
    CLOSE_CURL,
    OPEN_SQUARE,
    CLOSE_SQUARE,
    END_LINE,
    END_OF_FILE,
    IDENTIFIER,
};

struct Token
{
    TokenType type;
    std::string value;
};

class Lexer
{
public:
    Lexer(const std::string &source) : source_(source), position_(0) {}

    Token getNextToken();
    // Add other methods as needed

private:
    std::string source_;
    std::size_t position_;

    std::string lower(std::string str)
    {
        std::string lowered;
        for (int i = 0; i < str.size(); ++i) 
        {
            lowered += std::tolower(str[i]);
        }
        return lowered;
    }

    char getNextChar()
    {
        return source_[position_++];
    }

    void skipWhitespace()
    {
        while (position_ < source_.size() && std::isspace(source_[position_]))
        {
            position_++;
        }
    }

    TokenType getKeywordType(const std::string &identifier)
    {
        if (lower(identifier) == "if")
        {
            return TokenType::KEYWORD_IF;
        }
        else if (lower(identifier) == "else")
        {
            return TokenType::KEYWORD_ELSE;
        }
        else if (lower(identifier) == "elf")
        {
            return TokenType::KEYWORD_ELF;
        }
        else if (lower(identifier) == "do")
        {
            return TokenType::KEYWORD_DO;
        }
        else if (lower(identifier) == "while")
        {
            return TokenType::KEYWORD_WHILE;
        }
        else if (lower(identifier) == "for")
        {
            return TokenType::KEYWORD_FOR;
        }
        else if (lower(identifier) == "true")
        {
            return TokenType::KEYWORD_TRUE;
        }
        else if (lower(identifier) == "false")
        {
            return TokenType::KEYWORD_FALSE;
        }
        else if (lower(identifier) == "int")
        {
            return TokenType::KEYWORD_INTEGER;
        }
        else if (lower(identifier) == "bool" | lower(identifier) == "boolean")
        {
            return TokenType::KEYWORD_BOOLEAN;
        }
        else if (lower(identifier) == "char")
        {
            return TokenType::KEYWORD_CHAR;
        }
        else if (lower(identifier) == "str")
        {
            return TokenType::KEYWORD_STR;
        }
        else if (lower(identifier) == "string")
        {
            return TokenType::KEYWORD_STRING;
        }
        else if (lower(identifier) == "float")
        {
            return TokenType::KEYWORD_FLOAT;
        }
        else if (lower(identifier) == "double")
        {
            return TokenType::KEYWORD_DOUBLE;
        }
        // Add other keyword checks as needed

        return TokenType::IDENTIFIER;
    }

    Token readString()
    {
        std::string identifier;
        while (position_ < source_.size() && std::isalpha(source_[position_]))
        {
            identifier += getNextChar();
        }
        TokenType type = getKeywordType(identifier);
        return {type, identifier};
    }

    Token readNumber()
    {
        std::string number;
        while (position_ < source_.size() && std::isdigit(source_[position_]))
        {
            number += getNextChar();
        }
        return {TokenType::INTEGER, number};
    }
};

Token Lexer::getNextToken()
{
    skipWhitespace();

    if (position_ >= source_.size())
    {
        return {TokenType::END_OF_FILE, ""};
    }

    char currentChar = getNextChar();

    switch (currentChar)
    {
    case '+':
        return {TokenType::OPERATOR_ADD, "+"};
    case '-':
        return {TokenType::OPERATOR_SUBTRACT, "-"};
    case '*':
        return {TokenType::OPERATOR_MULTIPLY, "*"};
    case '/':
        return {TokenType::OPERATOR_DIVIDE, "/"};
    case '(':
        return {TokenType::OPEN_PAREN, "("};
    case ')':
        return {TokenType::CLOSE_PAREN, ")"};
    case '{':
        return {TokenType::OPEN_CURL, "{"};
    case '}':
        return {TokenType::CLOSE_CURL, "}"};
    case '[':
        return {TokenType::OPEN_SQUARE, "["};
    case ']':
        return {TokenType::CLOSE_SQUARE, "]"};
    case '"':
        return {TokenType::QUOTE, "\""};
    case ';':
        return {TokenType::END_LINE, ";"};
    }

    if (std::isalpha(currentChar))
    {
        position_--; // Unread the character
        return Lexer::readString();
    }

    if (std::isdigit(currentChar))
    {
        position_--; // Unread the character
        return Lexer::readNumber();
    }

    throw std::runtime_error("Unexpected character: " + std::string(1, currentChar));
}
