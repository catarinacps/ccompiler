/** lexer.l - Lexer specification definition
 *
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 * @author Bernardo Hummes <bhflores@inf.ufrgs.br>
 */

%{
#include "../../include/lexer/scanner.h"
%}

WHITE [[:space:]]

RK_INT "int"
RK_FLOAT "float"
RK_BOOL "bool"
RK_CHAR "char"
RK_IF "if"
RK_THEN "then"
RK_ELSE "else"
RK_WHILE "while"
RK_DO "do"
RK_INPUT "input"
RK_OUTPUT "output"
RK_RETURN "return"
RK_CONST "const"
RK_STATIC "static"
RK_FOREACH "foreach"
RK_FOR "for"
RK_SWITCH "switch"
RK_CASE "case"
RK_BREAK "break"
RK_CONTINUE "continue"
RK_CLASS "class"
RK_PRIVATE "private"
RK_PUBLIC "public"
RK_PROTECTED "protected"
RK_END "end"
RK_DEFAULT "default"

SPC_CHAR [,;:\(\)\[\]\{\}+\-|?@*/<>=!&%#ˆ.$]

DELIM ({SPC_CHAR}|{WHITE})

NOT_DELIM [^,;:\(\)\[\]\{\}+\-|?@*/<>=!&%#\ˆ.$[:space:]]

OP_LE "<="
OP_GE ">="
OP_EQ "=="
OP_NE "!="
OP_AND "&&"
OP_OR "||"
OP_SL ">>"
OP_SR "<<"

NUMBER [[:digit:]]
SCI_NOT [eE][+-]?{NUMBER}+

%x COMMENT
%x STRING
%x END_STRING
%x QUOTE
%x END_QUOTE
%x ID

%%

    /* block comments */
"/*"                                    { BEGIN(COMMENT); }
<COMMENT>[^*\n]*                        { }
<COMMENT>"*"+[^*/\n]*                   { }
<COMMENT>\n                             { }
<COMMENT>"*"+"/"                        { BEGIN(INITIAL); }

    /* line comments */
"//".*                                  { }

    /* reserved keywords */
{RK_INT}                                { V_LOG_LEXER("RK_INT"); return TK_PR_INT; }
{RK_FLOAT}                              { V_LOG_LEXER("RK_FLOAT"); return TK_PR_FLOAT; }
{RK_BOOL}                               { V_LOG_LEXER("RK_BOOL"); return TK_PR_BOOL; }
{RK_CHAR}                               { V_LOG_LEXER("RK_CHAR"); return TK_PR_CHAR; }
{RK_IF}                                 { V_LOG_LEXER("RK_IF"); return TK_PR_IF; }
{RK_THEN}                               { V_LOG_LEXER("RK_THEN"); return TK_PR_THEN; }
{RK_ELSE}                               { V_LOG_LEXER("RK_ELSE"); return TK_PR_ELSE; }
{RK_WHILE}                              { V_LOG_LEXER("RK_WHILE"); return TK_PR_WHILE; }
{RK_DO}                                 { V_LOG_LEXER("RK_DO"); return TK_PR_DO; }
{RK_INPUT}                              { V_LOG_LEXER("RK_INPUT"); return TK_PR_INPUT; }
{RK_OUTPUT}                             { V_LOG_LEXER("RK_OUTPUT"); return TK_PR_OUTPUT; }
{RK_RETURN}                             { V_LOG_LEXER("RK_RETURN"); return TK_PR_RETURN; }
{RK_CONST}                              { V_LOG_LEXER("RK_CONST"); return TK_PR_CONST; }
{RK_STATIC}                             { V_LOG_LEXER("RK_STATIC"); return TK_PR_STATIC; }
{RK_FOREACH}                            { V_LOG_LEXER("RK_FOREACH"); return TK_PR_FOREACH; }
{RK_FOR}                                { V_LOG_LEXER("RK_FOR"); return TK_PR_FOR; }
{RK_SWITCH}                             { V_LOG_LEXER("RK_SWITCH"); return TK_PR_SWITCH; }
{RK_CASE}                               { V_LOG_LEXER("RK_CASE"); return TK_PR_CASE; }
{RK_BREAK}                              { V_LOG_LEXER("RK_BREAK"); return TK_PR_BREAK; }
{RK_CONTINUE}                           { V_LOG_LEXER("RK_CONTINUE"); return TK_PR_CONTINUE; }
{RK_CLASS}                              { V_LOG_LEXER("RK_CLASS"); return TK_PR_CLASS; }
{RK_PRIVATE}                            { V_LOG_LEXER("RK_PRIVATE"); return TK_PR_PRIVATE; }
{RK_PUBLIC}                             { V_LOG_LEXER("RK_PUBLIC"); return TK_PR_PUBLIC; }
{RK_PROTECTED}                          { V_LOG_LEXER("RK_PROTECTED"); return TK_PR_PROTECTED; }
{RK_END}                                { V_LOG_LEXER("RK_END"); return TK_PR_END; }
{RK_DEFAULT}                            { V_LOG_LEXER("RK_DEFAULT"); return TK_PR_DEFAULT; }

    /* special characters */
{SPC_CHAR}                              { V_LOG_LEXER("SPECIAL"); return (int)*yytext;}

    /* composite operators  */
{OP_LE}                                 { V_LOG_LEXER("OP_LE"); return TK_OC_LE; }
{OP_GE}                                 { V_LOG_LEXER("OP_GE"); return TK_OC_GE; }
{OP_EQ}                                 { V_LOG_LEXER("OP_EQ"); return TK_OC_EQ; }
{OP_NE}                                 { V_LOG_LEXER("OP_NE"); return TK_OC_NE; }
{OP_AND}                                { V_LOG_LEXER("OP_AND"); return TK_OC_AND; }
{OP_OR}                                 { V_LOG_LEXER("OP_OR"); return TK_OC_OR; }
{OP_SL}                                 { V_LOG_LEXER("OP_SL"); return TK_OC_SL; }
{OP_SR}                                 { V_LOG_LEXER("OP_SR"); return TK_OC_SR; }

    /* string literals */
"\""                                    { BEGIN(STRING); }
<STRING>([^\"\n]|"\\"(?s:.))*/"\""      { BEGIN(END_STRING); return TK_LIT_STRING; }
<STRING>[^[:cntrl:]]+                   { BEGIN(INITIAL); return TOKEN_ERRO; }
<END_STRING>"\""                        { V_LOG_LEXER("STRING"); BEGIN(INITIAL); }

    /* character literals */
"\'"                                    { BEGIN(QUOTE); }
<QUOTE>"\\"?./"\'"                      { BEGIN(END_QUOTE); return TK_LIT_CHAR; }
<QUOTE>.                                { BEGIN(INITIAL); return TOKEN_ERRO; }
<END_QUOTE>"\'"                         { V_LOG_LEXER("CHAR"); BEGIN(INITIAL); }

    /* number literals */
[+-]?{NUMBER}+{NOT_DELIM}+/{DELIM}      { return TOKEN_ERRO; }
[+-]?{NUMBER}+\.{NUMBER}*{SCI_NOT}?     { V_LOG_LEXER("FLOAT"); return TK_LIT_FLOAT; }
[+-]?{NUMBER}+                          { V_LOG_LEXER("INT"); return TK_LIT_INT; }

    /* identifiers */
[[:alpha:]_][[:alnum:]_]*               { V_LOG_LEXER("IDENTIFIER"); return TK_IDENTIFICADOR; }

    /* whitespace or newlines between tokens */
{WHITE}                                 { }

    /* error catch-all */
<*>.|\n                                 { V_LOG_LEXER("UNKNOWN"); return TOKEN_ERRO; }

%%
