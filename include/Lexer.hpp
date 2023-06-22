#pragma once

#include <string>
#include "ILoveCpp.hpp"

class ilovecpp::Lexer{
    std::string input;
    int position = 0;
    int readPosition = 0;
    char ch;

public:
    Lexer() = delete;
    Lexer(std::string input);
    
    void ReadChar();
    Token NextToken();

    std::string ReadIdentifier();
};