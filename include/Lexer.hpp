#pragma once

#include <string>
#include "ILoveCpp.hpp"

class ilovecpp::Lexer{
public:
    std::string input;
    int position = 0;
    int readPosition = 0;
    char ch;

    Lexer() = delete;
    Lexer(std::string input);
    
    void ReadChar();
    Token NextToken();
    void GoTo(int position);

    std::string ReadIdentifier();
    std::string ReadNumber();
    std::string ReadOperator();
    std::string ReadString();
    
    void SkipWhitespace();
};