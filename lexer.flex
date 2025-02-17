%top{
    #include "parser.tab.hh"
    #include "Node.h"
    #define YY_DECL yy::parser::symbol_type yylex()
    int lexical_errors = 0;
}
%option yylineno noyywrap nounput batch noinput stack

%%
"="                     {if(USE_LEX_ONLY) {printf("ASSIGN ");} else {return yy::parser::make_ASSIGN(yytext); }}
"&&"                    {if(USE_LEX_ONLY) {printf("AND ");} else {return yy::parser::make_AND(yytext); }}
"||"                    {if(USE_LEX_ONLY) {printf("OR ");} else {return yy::parser::make_OR(yytext); }}
"=="                    {if(USE_LEX_ONLY) {printf("EQ ");} else {return yy::parser::make_EQ(yytext); }}
"<"                     {if(USE_LEX_ONLY) {printf("LT ");} else {return yy::parser::make_LT(yytext); }}
">"                     {if(USE_LEX_ONLY) {printf("GT ");} else {return yy::parser::make_GT(yytext); }}
"+"                     {if(USE_LEX_ONLY) {printf("ADD ");} else {return yy::parser::make_ADD(yytext); }}
"-"                     {if(USE_LEX_ONLY) {printf("SUB ");} else {return yy::parser::make_SUB(yytext); }}
"*"                     {if(USE_LEX_ONLY) {printf("MUL ");} else {return yy::parser::make_MUL(yytext); }}
"/"                     {if(USE_LEX_ONLY) {printf("DIV ");} else {return yy::parser::make_DIV(yytext); }}
"!"                     {if(USE_LEX_ONLY) {printf("NOT ");} else {return yy::parser::make_NOT(yytext); }}
"("                     {if(USE_LEX_ONLY) {printf("LP ");} else {return yy::parser::make_LP(yytext); }}
")"                     {if(USE_LEX_ONLY) {printf("RP ");} else {return yy::parser::make_RP(yytext); }}
"["                     {if(USE_LEX_ONLY) {printf("LHB ");} else {return yy::parser::make_LHB(yytext); }}
"]"                     {if(USE_LEX_ONLY) {printf("RHB ");} else {return yy::parser::make_RHB(yytext); }}
"{"                     {if(USE_LEX_ONLY) {printf("LBRACKET ");} else {return yy::parser::make_LBRACKET(yytext); }}
"}"                     {if(USE_LEX_ONLY) {printf("RBRACKET ");} else {return yy::parser::make_RBRACKET(yytext); }}
";"                     {if(USE_LEX_ONLY) {printf("SEMI ");} else {return yy::parser::make_SEMI(yytext); }}
","                     {if(USE_LEX_ONLY) {printf("COMMA ");} else {return yy::parser::make_COMMA(yytext); }}
"."                     {if(USE_LEX_ONLY) {printf("DOT ");} else {return yy::parser::make_DOT(yytext); }}
"class"                 {if(USE_LEX_ONLY) {printf("CLASS ");} else {return yy::parser::make_CLASS(yytext); }}
"main"                  {if(USE_LEX_ONLY) {printf("MAIN ");} else {return yy::parser::make_MAIN(yytext); }}
"public"                {if(USE_LEX_ONLY) {printf("PUBLIC ");} else {return yy::parser::make_PUBLIC(yytext); }}
"static"                {if(USE_LEX_ONLY) {printf("STATIC ");} else {return yy::parser::make_STATIC(yytext); }}
"void"                  {if(USE_LEX_ONLY) {printf("VOID ");} else {return yy::parser::make_VOID(yytext); }}
"if"                    {if(USE_LEX_ONLY) {printf("IF ");} else {return yy::parser::make_IF(yytext); }}
"else"                  {if(USE_LEX_ONLY) {printf("ELSE ");} else {return yy::parser::make_ELSE(yytext); }}
"while"                 {if(USE_LEX_ONLY) {printf("WHILE ");} else {return yy::parser::make_WHILE(yytext); }}
"System.out.println"    {if(USE_LEX_ONLY) {printf("PRINTLN ");} else {return yy::parser::make_PRINTLN(yytext); }}
"return"                {if(USE_LEX_ONLY) {printf("RETURN ");} else {return yy::parser::make_RETURN(yytext); }}
"int"                   {if(USE_LEX_ONLY) {printf("INT ");} else {return yy::parser::make_INT(yytext); }}
"boolean"               {if(USE_LEX_ONLY) {printf("BOOLEAN ");} else {return yy::parser::make_BOOLEAN(yytext); }}
"true"                  {if(USE_LEX_ONLY) {printf("TRUE ");} else {return yy::parser::make_TRUE(yytext); }}
"false"                 {if(USE_LEX_ONLY) {printf("FALSE ");} else {return yy::parser::make_FALSE(yytext); }}
"this"                  {if(USE_LEX_ONLY) {printf("THIS ");} else {return yy::parser::make_THIS(yytext); }}
"new"                   {if(USE_LEX_ONLY) {printf("NEW ");} else {return yy::parser::make_NEW(yytext); }}
"length"                {if(USE_LEX_ONLY) {printf("LENGTH ");} else {return yy::parser::make_LENGTH(yytext); }}
"String"                {if(USE_LEX_ONLY) {printf("STRING ");} else {return yy::parser::make_STRING(yytext); }}
[0-9]+                  {if(USE_LEX_ONLY) {printf("INT_LITERAL ");} else {return yy::parser::make_INT_LITERAL(yytext); }}
[a-zA-Z_][a-zA-Z0-9_]*  {if(USE_LEX_ONLY) {printf("IDENTIFIER ");} else {return yy::parser::make_IDENTIFIER(yytext); }}
[ \t\n\r]+              { /* ignore whitespace */ }
"//"[^\n]*              {}
    
. {if(!lexical_errors) fprintf(stderr, "Lexical errors found! See the logs below: \n"); fprintf(stderr,"\t@error at line %d. Character %s is not recognized\n", yylineno, yytext); lexical_errors = 1;}
<<EOF>> { return yy::parser::make_END(); }
%%