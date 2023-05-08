#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

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
    Lexer(const std::string &source) : source_(source), position_(0) {};
    Token getNextToken() { return tokens[++parserPos]; };
private:
    std::string source_;
    std::size_t position_;
    std::vector<Token> tokens;
    int parserPos;

    std::string lower(std::string str);
    char getNextChar();
    void skipWhitespace();
    TokenType getKeywordType(const std::string &identifier);
    Token readString();
    Token readNumber();
};

#endif
