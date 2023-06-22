#include "Lexer.hpp"
#include "Token.hpp"
#include <string>
#include <iostream>

using namespace ilovecpp;

Lexer::Lexer(std::string input){
    this->input = input;
    this->ReadChar();
}

void Lexer::ReadChar(){
    if(readPosition >= input.length()){
        this->ch = 0;
    }
    else{
        this->ch = this->input[this->readPosition];
    }

    this->position = this->readPosition;
    this->readPosition++;
}

Token Lexer::NextToken(){
    Token token;

    switch (this->ch) {
        // 구분자
        case ';':
            token = Token(Token::TokenType::SEMICOLON, this->ch);
            break;
        case ',':
            token = Token(Token::TokenType::COMMA, this->ch);
            break;
        
        case '(':
            token = Token(Token::TokenType::LPAREN, this->ch);
            break;
        case ')':
            token = Token(Token::TokenType::RPAREN, this->ch);
            break;
        case '{':
            token = Token(Token::TokenType::LBRACE, this->ch);
            break;
        case '}':
            token = Token(Token::TokenType::RBRACE, this->ch);
            break;
        case 0:
            token = Token(Token::TokenType::ENDOFFILE, "");
            break;

        default:
            if(Token::IsLetter(this->ch)){
                token.literal = this->ReadIdentifier();
                token.type = Token::LookUpIdent(token.literal);
                return token;
            }
            else{
                token = Token(Token::TokenType::ILLEGAL, this->ch);
            }
            break;
    }

    this->ReadChar();
    // return token;
}

std::string Lexer::ReadIdentifier(){
    std::string ident;
    int position = this->position;

    while(Token::IsLetter(this->ch)){
        ident += this->ch;
        this->ReadChar();
    }

    return ident;
}
