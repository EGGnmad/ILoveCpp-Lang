#include "Parser.hpp"
#include "Lexer.hpp"
#include <system_error>

using namespace ilovecpp;

Parser::Parser(Lexer* lexer){
    this->lexer = lexer;

    AdvanceToken();
    AdvanceToken();
}

void Parser::AdvanceToken(){
    curToken = peekToken;
    peekToken = lexer->NextToken();
}


std::string Parser::ParseProgram(){
    std::string result;


    while(curToken.type != Token::TokenType::ENDOFFILE){
        std::string now;

        if(curToken.type == Token::TokenType::IDENT){
            now = ParseInitVariableStatement().ToString();
        }
        // else{
        //     throw SyntaxErrorException();
        // }
        result += now + '\n';
    }

    return result;
}


//Node
IdentifierNode Parser::ParseIdentifierNode(){
    IdentifierNode node;
    node.ident = curToken;
    return node;
}

TypeNode Parser::ParseTypeNode(){
    TypeNode node;
    node.type = curToken;
    return node;
}

ValueNode Parser::ParseValueNode(){
    ValueNode node;
    node.value = curToken;
    return node;
}

OperatorNode Parser::ParseOperatorNode(){
    OperatorNode node;
    node.oper = curToken;
    return node;
}


//Expression
Expression Parser::ParseExpression(){

    //Value
    if(curToken.type == Token::TokenType::IDENT || curToken.type == Token::TokenType::NUMBER_INT || curToken.type == Token::TokenType::NUMBER_FLOAT || curToken.type == Token::TokenType::STRING){
        if(peekToken.type == Token::TokenType::PLUS || peekToken.type == Token::TokenType::MINUS || peekToken.type == Token::TokenType::MULTIPLY || peekToken.type == Token::TokenType::DIVIDE){
            Expression expr;
            expr.str = ParseOperatorExpression().ToString();

            return expr;
        }
        else if(peekToken.type == Token::TokenType::SEMICOLON){
            Expression expr;
            expr.str = ParseValueExpression().ToString();
            AdvanceToken();
            AdvanceToken();
            
            return expr;
        }
        else{
            throw SyntaxErrorException();
        }
    }
    else{
        throw SyntaxErrorException();
    }
}

IdentifierExpression Parser::ParseIdentifierExpression(){
    IdentifierExpression expr;
    expr.ident = ParseIdentifierNode();
    return expr;
}

TypeExpression Parser::ParseTypeExpression(){
    TypeExpression expr;
    expr.type = ParseTypeNode();
    return expr;
}


ValueExpression Parser::ParseValueExpression(){
    ValueExpression expr;
    expr.value = ParseValueNode();
    return expr;
}

OperatorExpression Parser::ParseOperatorExpression(){
    OperatorExpression expr;

    Expression exprTemp;
    exprTemp.str = ParseValueExpression().ToString();

    expr.left = exprTemp;
    AdvanceToken();

    expr.oper = ParseOperatorNode();
    AdvanceToken();

    expr.right = ParseExpression();

    return expr;
}


// Statement
InitVariableStatement Parser::ParseInitVariableStatement(){
    InitVariableStatement statement;

    statement.ident = ParseIdentifierExpression();
    AdvanceToken();

    if(curToken.type != Token::TokenType::DLEFT) throw SyntaxErrorException();
    AdvanceToken();

    if(curToken.type != Token::TokenType::TYPE_NUMBER_INT && curToken.type != Token::TokenType::TYPE_NUMBER_FLOAT && curToken.type != Token::TokenType::TYPE_BOOLEAN && curToken.type != Token::TokenType::TYPE_STRING){
        statement.value = ParseExpression();
    }

    else{
        statement.type = ParseTypeExpression();

        AdvanceToken();
        if(curToken.type != Token::TokenType::DLEFT) throw SyntaxErrorException();

        AdvanceToken();
        statement.value = ParseExpression();
    }

    return statement;
}

