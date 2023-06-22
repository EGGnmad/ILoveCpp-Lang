#pragma once

#include "ILoveCpp.hpp"
#include "Token.hpp"
#include "Expression.hpp"
#include "Statement.hpp"
#include <map>
#include <string>

class ilovecpp::Parser{
    Lexer* lexer;

public:
    ilovecpp::Token curToken;
    ilovecpp::Token peekToken;

    Parser(Lexer* lexer);
    void AdvanceToken();

    //Node
    IdentifierNode ParseIdentifierNode();
    TypeNode ParseTypeNode();
    ValueNode ParseValueNode();
    OperatorNode ParseOperatorNode();

    //Expression
    Expression ParseExpression();

    IdentifierExpression ParseIdentifierExpression();
    TypeExpression ParseTypeExpression();
    ValueExpression ParseValueExpression();
    OperatorExpression ParseOperatorExpression();

    //Statement
    InitVariableStatement ParseInitVariableStatement();

    //
    std::string ParseProgram();

    bool IsInitVariableStatement();
};