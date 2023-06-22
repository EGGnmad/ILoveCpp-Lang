#include "Token.hpp"

using namespace ilovecpp;

Token::Token(){
    this->type = TokenType::ENDOFFILE;
    this->literal = "";
}

Token::Token(TokenType type, std::string literal){
    this->type = type;
    this->literal = literal;
}

Token::Token(TokenType type, char ch){
    this->type = type;
    this->literal = std::string(1, ch);
}

Token& Token::operator=(Token token){
    this->type = token.type;
    this->literal = token.literal;
}
