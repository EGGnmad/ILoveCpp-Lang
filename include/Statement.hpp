#pragma once

#include "ILoveCpp.hpp"
#include "Node.hpp"
#include "Expression.hpp"
#include <string>

class ilovecpp::Statement : public Node{
};

class ProgramStatement : ilovecpp::Statement{
public:
    std::vector<ilovecpp::Statement> statements;

    std::string ToString() override{
        std::string result;

        for(ilovecpp::Statement statement : statements){
            result += statement.ToString() + "\n";
        }
        
        return result;
    }
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

class OutVariableStatement : ilovecpp::Statement{
public:
    ilovecpp::Expression value;
    
    std::string ToString(){
        return "std::cout <<" + value.ToString() + ";";
    }
};

class IfStatement : ilovecpp::Statement{
public:
    ilovecpp::Expression condition;
    ProgramStatement program;

    std::string ToString() override{
        return "if(" + condition.ToString() + "){\n" + program.ToString() + "}";
    }
};

class ElseStatement : ilovecpp::Statement{
public:
    ProgramStatement program;

    std::string ToString() override{
        return "else{\n" + program.ToString() + "}";
    }
};