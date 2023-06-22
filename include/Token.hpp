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
        NUMBER_INT,
        NUMBER_FLOAT,
        BOOLEAN,
        STRING,

        TYPE_NUMBER_INT,
        TYPE_NUMBER_FLOAT,
        TYPE_BOOLEAN,
        TYPE_STRING,

        // 연산자
        DLEFT, // <<
        PLUS, // <+<
        MINUS, // <-<
        MULTIPLY, // <*<
        DIVIDE, // </<

        LT, // <
        GT, // >
        BANG, // !

        // 구분자
        COMMA,      // ,
        SEMICOLON,  // ;

        LPAREN,     // (
        RPAREN,     // )
        LBRACE,     // {
        RBRACE,     // }

        // 예약어
        IF,
        ELSE,
        RETURN,
        OUT,
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

    static bool IsDigit(char ch){
        return '0' <= ch && ch <= '9';
    }

    static bool IsOperatorFirstCharacter(char ch){
        return ch == '<' || ch == '>' || ch == '!';
    }

    static bool IsOperatorCharacter(char ch){
        return ch == '<' || ch == '>' || ch == '!' || ch == '+' || ch == '-' || ch == '*' || ch == '/';
    }

    static bool IsString(char ch){
        return ch == '"';
    }

    static TokenType LookUpIdent(std::string ident){
        // fuck yes!!!
        std::map<std::string, TokenType> keywords = {
            {"int", TokenType::TYPE_NUMBER_INT},
            {"float", TokenType::TYPE_NUMBER_FLOAT},
            {"boolean", TokenType::TYPE_BOOLEAN},
            {"string", TokenType::TYPE_STRING},

            
            {"if", TokenType::IF},
            {"else", TokenType::ELSE},
            {"return", TokenType::RETURN},
            {"true", TokenType::BOOLEAN},
            {"false", TokenType::BOOLEAN},
            {"out", TokenType::OUT},
        };

        if(keywords.find(ident) != keywords.end()){
            return keywords[ident];
        }

        return TokenType::IDENT;
    }

    static TokenType LookUpOperator(std::string op){
        std::map<std::string, TokenType> keywords = {
            {"<<", TokenType::DLEFT},
            {"<+<", TokenType::PLUS},
            {"<-<", TokenType::MINUS},
            {"<*<", TokenType::MULTIPLY},
            {"</<", TokenType::DIVIDE},
            {"<", TokenType::LT},
            {">", TokenType::GT},
            {"!", TokenType::BANG},
        };

        if(keywords.find(op) != keywords.end()){
            return keywords[op];
        }

        return TokenType::ILLEGAL;
    }

    static TokenType LookNumberType(std::string number){
        bool hasDot = false;

        for(char c : number){
            if(c == '.' && !hasDot){
                hasDot = true;
            }
            else if(c == '.' && hasDot){
                return TokenType::ILLEGAL;
            }
        }

        if(!hasDot)
            return TokenType::NUMBER_INT;
        else
            return TokenType::NUMBER_FLOAT;
    }
};