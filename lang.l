%{
//**************************************
// lang.l
//
// Scanner definition file for CST 320 project
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//
// Modified: Mark A Shanklin
// mark.shanklin@oit.edu
// 
// Date: Jan. 19, 2016
//

#include "tokens.h"
#include "lex.h"
#include "cSymbol.h"
#include "cSymbolTable.h"

#define DO_RETURN(a) return (a)
//#define DO_RETURN(a) return Return(a)
int Return(int val);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. period is an example. */
period          	['.']
int_val			[0-9]+
float_val		(([1-9][0-9]*)|0)\.[0-9]+
identifier		[a-zA-Z][a-zA-Z0-9]*
		
%%

    // token definitions go here. "if" is an example.
"if"                        	DO_RETURN(IF);
"endif"                        	DO_RETURN(ENDIF);
"else"                        	DO_RETURN(ELSE);
"while"                        	DO_RETURN(WHILE);
"print"                        	DO_RETURN(PRINT);
"int"                        	DO_RETURN(INT);
"float"                        	DO_RETURN(FLOAT);
"char"                        	DO_RETURN(CHAR);
"struct"                        DO_RETURN(STRUCT);
"return"                        DO_RETURN(RETURN);
{int_val}                       DO_RETURN(INT_VAL);
{float_val}                     DO_RETURN(FLOAT_VAL);
{identifier}                    {
                                    extern cSymbolTable g_SymbolTable;
                                    yylval.symbol = g_SymbolTable.Insert(yytext);
                                    return IDENTIFIER;
                                }
"=="                        	DO_RETURN(EQUALS);
"&&"                        	DO_RETURN(AND);
"||"                        	DO_RETURN(OR);
"//".*$				{}
[ \t\n\r]*			{}
"."				DO_RETURN('.');
"("				DO_RETURN('(');
")"				DO_RETURN(')');
"{"				{
                                    extern cSymbolTable g_SymbolTable;
                                    g_SymbolTable.IncreaseScope();
                                    return yytext[0];
                                }
"}"				{
                                    extern cSymbolTable g_SymbolTable;
                                    g_SymbolTable.DecreaseScope();
                                    return yytext[0];
                                }
"["				DO_RETURN('[');
"]"				DO_RETURN(']');
";"				DO_RETURN(';');
","				DO_RETURN(',');
"+"				DO_RETURN('+');
"-"				DO_RETURN('-');
"*"				DO_RETURN('*');
"/"				DO_RETURN('/');
"%"				DO_RETURN('%');
"="				DO_RETURN('=');
"_"                             DO_RETURN('_');
.				DO_RETURN(JUNK_TOKEN);

%%

// This function allows us to do extra processing on each token
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

