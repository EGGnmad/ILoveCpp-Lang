#include <iostream>
#include "Lexer.hpp"
#include "Token.hpp"


using namespace std;
using namespace ilovecpp;

int main(){
    Lexer lexer = Lexer("let");
    Token token = lexer.NextToken();
    cout << (int)token.type << " " << token.literal << "\n";

    token = lexer.NextToken();
    // cout << (int)token.type << " " << token.literal << "\n";
}