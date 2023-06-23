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

void Lexer::GoTo(int position){
    this->readPosition = position;
    ReadChar();   
}

Token Lexer::NextToken(){
    Token token;

    this->SkipWhitespace();

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
            // 연산자
            if(Token::IsOperatorFirstCharacter(this->ch)){
                token.literal = this->ReadOperator();
                token.type = Token::LookUpOperator(token.literal);
                return token;
            }
            // 문자
            else if(Token::IsLetter(this->ch)){
                token.literal = this->ReadIdentifier();
                token.type = Token::LookUpIdent(token.literal);
                return token;
            }
            // 숫자
            else if(Token::IsDigit(this->ch)){
                token.literal = this->ReadNumber();
                token.type = Token::LookNumberType(token.literal);
                if(token.type == Token::TokenType::NUMBER_FLOAT)
                    token.literal += "f";

                return token;
            }

            else if(Token::IsString(this->ch)){
                token.literal = this->ReadString();
                
                if(token.literal == "ILLEGAL")
                    token.type = Token::TokenType::ILLEGAL;
                else
                    token.type = Token::TokenType::STRING;
            }

            else{
                token = Token(Token::TokenType::ILLEGAL, this->ch);
            }
            break;
    }

    this->ReadChar();
    return token;
}

std::string Lexer::ReadIdentifier(){
    std::string ident;

    while(Token::IsLetter(this->ch)){
        ident += this->ch;
        this->ReadChar();
    }

    return ident;
}

std::string Lexer::ReadNumber(){
    std::string number;

    while(Token::IsDigit(this->ch) || this->ch == '.'){
        number += this->ch;
        this->ReadChar();
    }

    return number;
}

std::string Lexer::ReadOperator(){
    std::string op;

    while(Token::IsOperatorCharacter(this->ch)){
        op += this->ch;
        this->ReadChar();
    }

    return op;
}

std::string Lexer::ReadString(){
    std::string str;
    str += '"';
    this->ReadChar();

    while(!Token::IsString(this->ch)){
        if(this->ch == 0)
            return "ILLEGAL";

        str += this->ch;
        this->ReadChar();
    }

    str += '"';
    return str;
}

void Lexer::SkipWhitespace(){
    while(this->ch == ' ' || this->ch == '\t' || this->ch == '\n' || this->ch == '\r') this->ReadChar();
}