%{
//**************************************
// minc.y
//
// Parser definition file. bison uses this file to generate the parser.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Feb. 25, 2016
//
#include <iostream>
#include "lex.h"

%}

%locations

 /* union defines the type for lexical values */
%union{
    int             int_val;
    double          float_val;
    }

%{
    int yyerror(const char *msg);
%}

%start  program

%token IDENTIFIER
%token INT_VAL FLOAT_VAL
%token PRINT PRINT_F IF GOTO RETURN
%token NEQUALS EQUALS PLUS_EQUALS MINUS_EQUALS
%token HEADER1 HEADER2 HEADER3 HEADER4 HEADER5 HEADER6 HEADER7
%token MAIN INT DOUBLE 
%token FRAME_PTR STACK_PTR TEMP TEMP_F MEMORY
%token JUNK_TOKEN

%type <int_val> program
%type <int_val> header
%type <int_val> main
%type <int_val> funcs
%type <int_val> stmts
%type <int_val> stmt

%%

program: header main funcs      { 
                                  if (yynerrs == 0) 
                                      YYACCEPT;
                                  else
                                      YYABORT;
                                }
header: HEADER1 HEADER2 HEADER3 HEADER4 HEADER5 HEADER6 HEADER7 {}

main: INT MAIN '(' ')' '{' stmts RETURN '0' ';' '}'             {}
funcs: funcs func                                               {}
        | func                                                  {}
        | /* none */                                            {}

func: INT IDENTIFIER '(' ')' '{' stmts RETURN '0' ';' '}'       {}

stmts:      stmts stmt                                          {}
        |   stmt                                                {}

stmt:       IF '(' expr ')' GOTO IDENTIFIER ';'                 {}
        |   PRINT ';'                                           {}
        |   PRINT_F ';'                                         {}
        |   lval '=' expr ';'                                   {} 
        |   lval '=' reg ';'                                    {} 
        |   reg PLUS_EQUALS int_val ';'                         {} 
        |   reg MINUS_EQUALS int_val ';'                        {} 
        |   func_call ';'                                       {}
        |   GOTO IDENTIFIER ';'                                 {}
        |   IDENTIFIER ':'                                      {}
        |   error ';'                                           {}

func_call:  IDENTIFIER '(' ')'                                  {}

lval:       memref                                              {}
        |   reg                                                 {}

reg:        FRAME_PTR                                           {}
        |   STACK_PTR                                           {}
        |   TEMP                                                {}
        |   TEMP_F                                              {}

memref:  MEMORY '[' index ']'                                   {}
        | '*' '(' INT '*' ')' '&' MEMORY '[' index ']'          {}
        | '*' '(' DOUBLE '*' ')' '&' MEMORY '[' index ']'       {}
        
index:    int_val                                               {}
        | FRAME_PTR '+' int_val                                 {}
        | FRAME_PTR '-' int_val                                 {}
        | FRAME_PTR                                             {}
        | STACK_PTR                                             {}

expr:       expr EQUALS add                                     {}
        |   expr NEQUALS add                                    {}
        |   add                                                 {}

add:        add '+' term                                        {}
        |   add '-' term                                        {}
        |   term                                                {}

term:       term '*' fact                                       {}
        |   term '/' fact                                       {}
        |   term '%' fact                                       {}
        |   fact                                                {}

fact:        '(' expr ')'                                       {}
        |   int_val                                             {}
        |   FLOAT_VAL                                           {}
        |   memref                                              {}

int_val:    '0'                                                 {}
        |   INT_VAL                                             {}
%%

// Function to format error messages
int yyerror(const char *msg)
{
    std::cerr << "ERROR: " << msg << " at symbol '"
        << yytext << "' on line " << yylineno << "\n";

    return 0;
}

