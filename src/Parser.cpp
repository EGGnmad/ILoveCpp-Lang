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


ProgramStatement Parser::ParseProgram(){
    ProgramStatement program;

    while(curToken.type != Token::TokenType::ENDOFFILE && curToken.type != Token::TokenType::RBRACE){
        Statement statement = ParseStatement();
        program.statements.push_back(statement);
    }

    return program;
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
    if(curToken.type == Token::TokenType::IDENT || curToken.type == Token::TokenType::NUMBER_INT || curToken.type == Token::TokenType::NUMBER_FLOAT || curToken.type == Token::TokenType::BOOLEAN || curToken.type == Token::TokenType::STRING){
        if(peekToken.type == Token::TokenType::PLUS || peekToken.type == Token::TokenType::MINUS || peekToken.type == Token::TokenType::MULTIPLY || peekToken.type == Token::TokenType::DIVIDE || peekToken.type == Token::TokenType::LT || peekToken.type == Token::TokenType::GT){
            Expression expr;
            expr.str = ParseOperatorExpression().ToString();

            return expr;
        }
        else if(peekToken.type == Token::TokenType::DLEFT){
            Expression expr;
            expr.str = ParseValueExpression().ToString();
            AdvanceToken();
            AdvanceToken();

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
Statement Parser::ParseStatement(){
    Statement statement;

    if(curToken.type == Token::TokenType::IDENT){
        statement.str = ParseInitVariableStatement().ToString();
    }
    else if(curToken.type == Token::TokenType::OUT){
        statement.str = ParseOutVariableStatement().ToString();
    }
    else if(curToken.type == Token::TokenType::IF){
        statement.str = ParseIfStatement().ToString();
    }
    else if(curToken.type == Token::TokenType::ELSE){
        statement.str = ParseElseStatement().ToString();
    }
    return statement;
}


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

OutVariableStatement Parser::ParseOutVariableStatement(){
    OutVariableStatement statement = OutVariableStatement();

    AdvanceToken();
    if(curToken.type != Token::TokenType::DLEFT) throw SyntaxErrorException();

    AdvanceToken();

    statement.value = ParseExpression();

    return statement;
}

IfStatement Parser::ParseIfStatement(){
    IfStatement statement;
    
    AdvanceToken();
    if(curToken.type != Token::TokenType::DLEFT) throw SyntaxErrorException();

    AdvanceToken();
    statement.condition = ParseExpression();

    if(curToken.type != Token::TokenType::LBRACE) throw SyntaxErrorException();

    AdvanceToken();
    statement.program = ParseProgram();

    AdvanceToken();

    return statement;
}

ElseStatement Parser::ParseElseStatement(){
    ElseStatement statement;

    AdvanceToken();
    if(curToken.type != Token::TokenType::DLEFT) throw SyntaxErrorException();

    AdvanceToken();
    if(curToken.type != Token::TokenType::LBRACE) throw SyntaxErrorException();

    AdvanceToken();
    statement.program = ParseProgram();

    AdvanceToken();

    return statement;
}