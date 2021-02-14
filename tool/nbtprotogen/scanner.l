%{
#include <string>
#include <vector>
#include "token.h"

int line_num = 1;
int col_num = 1;

std::vector<Lex::Token> lex_output;
%}

%option noyywrap c++
%option header-file="lex.yy.h"

string  \"[^\n"]+\"

ws      [ \t]+

alpha   [A-Za-z]
dig     [0-9]
name    ({alpha}|{dig}|\$)({alpha}|{dig}|[_\-/$])*
num1    [-+]?{dig}+\.?([eE][-+]?{dig}+)?
num2    [-+]?{dig}*\.{dig}+([eE][-+]?{dig}+)?
number  {num1}|{num2}

%%

{ws}    { col_num += YYLeng(); }


"/*"    {
        int c;
        col_num += 2;

        while((c = yyinput()) != 0) {
            ++col_num;
            if(c == '\n') {
                ++line_num;
                col_num = 1;
            }

            else if(c == '*') {
                if((c = yyinput()) == '/') {
                    ++col_num;
                    break;
                }
                else {
                    unput(c);
                }
            }
        }
        }

{number} {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::Integer,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

{string} {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::String,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

"syntax" {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::Syntax,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

"package" {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::Package,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

"message" {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::Message,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

"=" {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::EqualSign,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

"." {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::Dot,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

"," {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::Comma,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

";" {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::SemiCol,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

"{" {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::LeftBrace,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

"}" {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::RightBrace,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

"[" {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::LeftSquare,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

"]" {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::RightSquare,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

"<" {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::LeftAngle,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

">" {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::RightAngle,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

{name}   {
            lex_output.emplace_back(Lex::Token{
                    .value{YYText()},
                    .tt = Lex::TokenType::Identifier,
                    .line = line_num,
                    .col = col_num,
            });
            col_num += YYLeng();
         }

\n      {++line_num; col_num = 1;}

.       {++col_num;}
%%
