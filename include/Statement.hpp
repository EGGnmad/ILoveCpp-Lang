#pragma once

#include "ILoveCpp.hpp"
#include "Node.hpp"
#include "Expression.hpp"

class ilovecpp::Statement : public Node{
};

class InitVariableStatement : ilovecpp::Statement{
public:
    IdentifierExpression ident;
    TypeExpression type;
    ilovecpp::Expression value;

    std::string ToString(){
        return type.ToString() + " " + ident.ToString() + " = " + value.ToString() + ";";
    }
};