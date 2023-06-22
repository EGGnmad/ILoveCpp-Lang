#pragma once

#include "ILoveCpp.hpp"
#include "Node.hpp"
#include <string>

class ilovecpp::Expression : public Node{
};

class IdentifierExpression : public ilovecpp::Expression{
public:
    IdentifierNode ident;

    std::string ToString() override{
        return ident.ToString();
    }
};

class TypeExpression : public ilovecpp::Expression{
public:
    TypeNode type;

    std::string ToString() override{
        return type.ToString();
    }
};

class ValueExpression : public ilovecpp::Expression{
public:
    ValueNode value;

    std::string ToString() override{
        return value.ToString();
    }
};

class OperatorExpression : public ilovecpp::Expression{
public:
    Expression left;
    OperatorNode oper;
    Expression right;

    std::string ToString() override{
        return left.ToString() + oper.ToString() + right.ToString();
    }
};