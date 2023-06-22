#pragma once

#include <string>
#include <map>
#include "ILoveCpp.hpp"

struct ilovecpp::Token{
public:
    enum class TokenType{
        ILLEGAL,
        ENDOFFILE, //EOF already defined

        //식별자 & 리터럴
        IDENT,
        INT,

        // 연산자
        ASSIGN,     //
        PLUS,       //

        // 구분자
        COMMA,      // ,
        SEMICOLON,  // ;

        LPAREN,     // (
        RPAREN,     // )
        LBRACE,     // {
        RBRACE,     // }

        // 예약어
        FUNCTION,
        LET,
    };

public:
    TokenType type;
    std::string literal;

    Token();
    Token(TokenType type, std::string literal);
    Token(TokenType type, char ch);

    Token& operator=(Token token);

    static bool IsLetter(char ch){
        return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch =='_';
    }

    static TokenType LookUpIdent(std::string ident){
        // fuck yes!!!
        std::map<std::string, TokenType> keywords = {
            {"let", TokenType::LET},
            {"function", TokenType::FUNCTION},
        };

        if(keywords.find(ident) != keywords.end()){
            return keywords[ident];
        }

        return TokenType::IDENT;
    }
};