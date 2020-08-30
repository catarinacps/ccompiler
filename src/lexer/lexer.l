/** lexer.l - Lexer specification definition
 *
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 * @author Bernardo Hummes <bhflores@inf.ufrgs.br>
 */

%{
#include "../../include/lexer/lexer.h"
%}

WHITE [[:blank:]]

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

SPC_CHAR [,;:\(\)\[\]\{\}+-|?@*/<>=!&%#ˆ.$]

%x COMMENT
%x WORD
%x STRING
%x QUOTE

%%

    /* block comments */
"/*"                           { BEGIN(COMMENT); }
<COMMENT>[^*\n]*               { }
<COMMENT>"*"+[^*/\n]*          { }
<COMMENT>\n                    { }
<COMMENT>"*"+"/"               { V_LOG_LEXER(); BEGIN(INITIAL); }

    /* line comments */
"//".*                         { V_LOG_LEXER(); }

    /* reserved keywords */
{RK_INT}                       { V_LOG_LEXER(); return TK_PR_INT; }
{RK_FLOAT}                     { V_LOG_LEXER(); return TK_PR_FLOAT; }
{RK_BOOL}                      { V_LOG_LEXER(); return TK_PR_BOOL; }
{RK_CHAR}                      { V_LOG_LEXER(); return TK_PR_CHAR; }
{RK_IF}                        { V_LOG_LEXER(); return TK_PR_IF; }
{RK_THEN}                      { V_LOG_LEXER(); return TK_PR_THEN; }
{RK_ELSE}                      { V_LOG_LEXER(); return TK_PR_ELSE; }
{RK_WHILE}                     { V_LOG_LEXER(); return TK_PR_WHILE; }
{RK_DO}                        { V_LOG_LEXER(); return TK_PR_DO; }
{RK_INPUT}                     { V_LOG_LEXER(); return TK_PR_INPUT; }
{RK_OUTPUT}                    { V_LOG_LEXER(); return TK_PR_OUTPUT; }
{RK_RETURN}                    { V_LOG_LEXER(); return TK_PR_RETURN; }
{RK_CONST}                     { V_LOG_LEXER(); return TK_PR_CONST; }
{RK_STATIC}                    { V_LOG_LEXER(); return TK_PR_STATIC; }
{RK_FOREACH}                   { V_LOG_LEXER(); return TK_PR_FOREACH; }
{RK_FOR}                       { V_LOG_LEXER(); return TK_PR_FOR; }
{RK_SWITCH}                    { V_LOG_LEXER(); return TK_PR_SWITCH; }
{RK_CASE}                      { V_LOG_LEXER(); return TK_PR_CASE; }
{RK_BREAK}                     { V_LOG_LEXER(); return TK_PR_BREAK; }
{RK_CONTINUE}                  { V_LOG_LEXER(); return TK_PR_CONTINUE; }
{RK_CLASS}                     { V_LOG_LEXER(); return TK_PR_CLASS; }
{RK_PRIVATE}                   { V_LOG_LEXER(); return TK_PR_PRIVATE; }
{RK_PUBLIC}                    { V_LOG_LEXER(); return TK_PR_PUBLIC; }
{RK_PROTECTED}                 { V_LOG_LEXER(); return TK_PR_PROTECTED; }
{RK_END}                       { V_LOG_LEXER(); return TK_PR_END; }
{RK_DEFAULT}                   { V_LOG_LEXER(); return TK_PR_DEFAULT; }

    /* special characters */
{SPC_CHAR}                     { V_LOG_LEXER(); return (int)*yytext;}

    /* string literals */
"\""                           { BEGIN(STRING); }
<STRING>([^\"\n]|"\\"(?s:.))*  { }
<STRING>"\""                   { V_LOG_LEXER(); BEGIN(INITIAL); }

    /* character literals */
"\'"                           { BEGIN(QUOTE); }
<QUOTE>"\\"?.                  { }
<QUOTE>"\'"                    { V_LOG_LEXER(); BEGIN(INITIAL); }

    /* whitespace or newlines between tokens */
{WHITE}|\na                    { }

    /* error catch-all */
<*>.|\n                        { ECHO; }

%%
