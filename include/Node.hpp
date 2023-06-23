#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "ILoveCpp.hpp"
#include "Token.hpp"
#include "Exception.hpp"

class ilovecpp::Node{
public:
    std::string str;
    virtual std::string ToString(){
        return str;
    }
};

class IdentifierNode : public ilovecpp::Node{
public:
    ilovecpp::Token ident;

    std::string ToString() override{
        return ident.literal;
    }
};

class TypeNode : public ilovecpp::Node{
public:
    ilovecpp::Token type;

    std::string ToString() override{
        switch (type.type) {
            case ilovecpp::Token::TokenType::TYPE_NUMBER_INT:
                return "int";
            case ilovecpp::Token::TokenType::TYPE_NUMBER_FLOAT:
                return "float";
            case ilovecpp::Token::TokenType::TYPE_BOOLEAN:
                return "bool";
            case ilovecpp::Token::TokenType::TYPE_STRING:
                return "std::string";
            default:
                return type.literal;
        }
    }
};

class ValueNode : public ilovecpp::Node{
public:
    ilovecpp::Token value;

    std::string ToString() override{
        return value.literal;
    }
};

class OperatorNode : public ilovecpp::Node{
public:
    ilovecpp::Token oper;

    std::string ToString() override{
        std::string str;

        switch (oper.type) {
            case ilovecpp::Token::TokenType::PLUS:
                str = "+";
                break;
            case ilovecpp::Token::TokenType::MINUS:
                str = "-";
                break;
            case ilovecpp::Token::TokenType::MULTIPLY:
                str = "*";
                break;
            case ilovecpp::Token::TokenType::DIVIDE:
                str = "/";
                break;
            case ilovecpp::Token::TokenType::LT:
                str = "<";
                break;
            case ilovecpp::Token::TokenType::GT:
                str = ">";
                break;
            default:
                break;
        }

        return str;
    }
};