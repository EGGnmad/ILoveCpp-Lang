#pragma once


#include <iostream>

class Exception{
public:
    virtual void report(){
        std::cerr << "throw Exception";
    }
};

class SyntaxErrorException : public Exception{
public:
    void report() override{
        std::cerr << "Syntax Error";
    }
};

class UndefinedTypeErrorException : public Exception{
public:
    void report() override{
        std::cerr << "Undefined Type Error";
    }
};