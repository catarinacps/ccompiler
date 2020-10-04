/** lexer.l - Lexer specification definition
 *
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 * @author Bernardo Hummes <bhflores@inf.ufrgs.br>
 */

%{
#include "lexer/scanner.h"
/* to track the initial column of matched tokens */
int yycolumn = 1;
/* to save the line of the current matches*/
char* yylinebuf = NULL;
size_t yylinebuf_len = 0;

/* helpful flex feature that helps us to track the location of the tokens */
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
%}

/* no need to use the default flex main */
%option noyywrap yylineno

/* helpful character classes */
WHITE [[:blank:]]
GRAPH [[:graph:]]
ALNUM [[:alnum:]_]
ALPHA [[:alpha:]_]

/* to handle escape sequences require the modification of the matched
 * string, which is not a good idea to do with yytext, as it points
 * directly to the input stream */
ESC_SEQ [abfnrtv\\\"\']

/* reserved keywords */
RK_INT "int"
RK_FLOAT "float"
RK_BOOL "bool"
RK_CHAR "char"
RK_STRING "string"
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

/* special punctuation characters */
SPC_CHAR [[:punct:]]{-}[\'\"\`_~\\]

/* delimiters, which are either whitespace or special punctuation
 * characters */
DELIM [[:punct:][:space:]]{-}[_\\~]

/* composite operators */
OP_LE "<="
OP_GE ">="
OP_EQ "=="
OP_NE "!="
OP_AND "&&"
OP_OR "||"
OP_SL "<<"
OP_SR ">>"

/* decimals */
NUMBER [[:digit:]]
SCI_NOT [eE][+\-]?{NUMBER}+

/* boolean literals */
BOOL_T "true"
BOOL_F "false"

/* states */
%x NORMAL
%x COMMENT
%x WORD
%x STRING
%x QUOTE
%x ID
%x DECIMAL

%%

    /* ----------  first read line ---------- */

    /* note that this rule is only here so we can save the first line of
     * input to the error function */
.*                                     {
    /* if our line buffer is small, we grow it by 100 characters */
    cc_update_line_buffer(yytext, yyleng);
    yycolumn = 1;
    yyless(0);
    BEGIN(NORMAL);
}

    /* ----------  comments section ----------  */

    /* block comment*/
<NORMAL>"/*"                           { BEGIN(COMMENT); V_LOG_LEXER("COMMENT STATE"); }

    /* comment state */
<COMMENT>{

"*"+"/"                                { BEGIN(NORMAL); V_LOG_LEXER("INITIAL STATE"); }
[^*\n]*
"*"+[^*/\n]*
\n                                     { yycolumn = 1; }
<<EOF>>                                { return TOKEN_ERRO; }

}

    /* line comments */
<NORMAL>"//".*                         { yycolumn = 1; }


    /* ----------  words section ----------  */

<NORMAL>{ALPHA}/{ALNUM}*               {
    BEGIN(WORD);
    V_LOG_LEXER("WORD STATE");
    yycolumn -= yyleng;
    yyless(0);
    }


    /* word state */
<WORD>{

    /* reserved keywords */
{RK_INT}                               { V_LOG_LEXER("RK_INT"); return TK_PR_INT; }
{RK_FLOAT}                             { V_LOG_LEXER("RK_FLOAT"); return TK_PR_FLOAT; }
{RK_BOOL}                              { V_LOG_LEXER("RK_BOOL"); return TK_PR_BOOL; }
{RK_CHAR}                              { V_LOG_LEXER("RK_CHAR"); return TK_PR_CHAR; }
{RK_STRING}                            { V_LOG_LEXER("RK_STRING"); return TK_PR_STRING; }
{RK_IF}                                {
    cc_node_data_t input = { .cmd = cc_cmd_if };
    yylval.lexic_value = cc_create_lexic_value(input, cc_cmd, cc_match_line_number());
    V_LOG_LEXER("RK_IF");
    return TK_PR_IF;
    }
{RK_THEN}                              { V_LOG_LEXER("RK_THEN"); return TK_PR_THEN; }
{RK_ELSE}                              { V_LOG_LEXER("RK_ELSE"); return TK_PR_ELSE; }
{RK_WHILE}                             {
    cc_node_data_t input = { .cmd = cc_cmd_while };
    yylval.lexic_value = cc_create_lexic_value(input, cc_cmd, cc_match_line_number());
    V_LOG_LEXER("RK_WHILE");
    return TK_PR_WHILE;
    }
{RK_DO}                                { V_LOG_LEXER("RK_DO"); return TK_PR_DO; }
{RK_INPUT}                             {
    cc_node_data_t input = { .cmd = cc_cmd_input };
    yylval.lexic_value = cc_create_lexic_value(input, cc_cmd, cc_match_line_number());
    V_LOG_LEXER("RK_INPUT");
    return TK_PR_INPUT;
    }
{RK_OUTPUT}                            {
    cc_node_data_t input = { .cmd = cc_cmd_output };
    yylval.lexic_value = cc_create_lexic_value(input, cc_cmd, cc_match_line_number());
    V_LOG_LEXER("RK_OUTPUT");
    return TK_PR_OUTPUT;
    }
{RK_RETURN}                            {
    cc_node_data_t input = { .cmd = cc_cmd_return };
    yylval.lexic_value = cc_create_lexic_value(input, cc_cmd, cc_match_line_number());
    V_LOG_LEXER("RK_RETURN");
    return TK_PR_RETURN;
    }
{RK_CONST}                             { V_LOG_LEXER("RK_CONST"); return TK_PR_CONST; }
{RK_STATIC}                            { V_LOG_LEXER("RK_STATIC"); return TK_PR_STATIC; }
{RK_FOREACH}                           { V_LOG_LEXER("RK_FOREACH"); return TK_PR_FOREACH; }
{RK_FOR}                               {
    cc_node_data_t input = { .cmd = cc_cmd_for };
    yylval.lexic_value = cc_create_lexic_value(input, cc_cmd, cc_match_line_number());
    V_LOG_LEXER("RK_FOR");
    return TK_PR_FOR;
    }
{RK_SWITCH}                            { V_LOG_LEXER("RK_SWITCH"); return TK_PR_SWITCH; }
{RK_CASE}                              { V_LOG_LEXER("RK_CASE"); return TK_PR_CASE; }
{RK_BREAK}                             {
    cc_node_data_t input = { .cmd = cc_cmd_break };
    yylval.lexic_value = cc_create_lexic_value(input, cc_cmd, cc_match_line_number());
    V_LOG_LEXER("RK_BREAK");
    return TK_PR_BREAK;
    }
{RK_CONTINUE}                          {
    cc_node_data_t input = { .cmd = cc_cmd_continue };
    yylval.lexic_value = cc_create_lexic_value(input, cc_cmd, cc_match_line_number());
    V_LOG_LEXER("RK_CONTINUE");
    return TK_PR_CONTINUE;
    }
{RK_CLASS}                             { V_LOG_LEXER("RK_CLASS"); return TK_PR_CLASS; }
{RK_PRIVATE}                           { V_LOG_LEXER("RK_PRIVATE"); return TK_PR_PRIVATE; }
{RK_PUBLIC}                            { V_LOG_LEXER("RK_PUBLIC"); return TK_PR_PUBLIC; }
{RK_PROTECTED}                         { V_LOG_LEXER("RK_PROTECTED"); return TK_PR_PROTECTED; }
{RK_END}                               { V_LOG_LEXER("RK_END"); return TK_PR_END; }
{RK_DEFAULT}                           { V_LOG_LEXER("RK_DEFAULT"); return TK_PR_DEFAULT; }

    /* boolean literals */
{BOOL_T}                               {
    cc_node_data_t input = { .lit = { cc_type_bool, { .boolean = true } } };
    yylval.lexic_value = cc_create_lexic_value(input, cc_lit, cc_match_line_number());
    V_LOG_LEXER("TRUE");
    return TK_LIT_TRUE;
    }
{BOOL_F}                               {
    cc_node_data_t input = { .lit = { cc_type_bool, { .boolean = false } } };
    yylval.lexic_value = cc_create_lexic_value(input, cc_lit, cc_match_line_number());
    V_LOG_LEXER("FALSE");
    return TK_LIT_FALSE;
    }

    /* identifiers */
{ALPHA}{ALNUM}*                        {
    /* TODO: add read string to global set */
    cc_node_data_t input = { .id = strndup(yytext, yyleng) };
    yylval.lexic_value = cc_create_lexic_value(input, cc_id, cc_match_line_number());
    V_LOG_LEXER("IDENTIFIER");
    return TK_IDENTIFICADOR;
    }

    /* end word */
{DELIM}                                {
    BEGIN(NORMAL);
    V_LOG_LEXER("INITIAL STATE");
    yyless(0);
    yycolumn--;
    }

}


    /* ---------- special characters section ----------  */

    /* composite operators */
<NORMAL>{OP_LE}                        { V_LOG_LEXER("OP_LE"); return TK_OC_LE; }
<NORMAL>{OP_GE}                        {
    cc_node_data_t input = { .expr = cc_expr_log_ge };
    yylval.lexic_value = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    V_LOG_LEXER("OP_GE");
    return TK_OC_GE;
    }
<NORMAL>{OP_EQ}                        {
    cc_node_data_t input = { .expr = cc_expr_log_eq };
    yylval.lexic_value = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    V_LOG_LEXER("OP_EQ");
    return TK_OC_EQ;
    }
<NORMAL>{OP_NE}                        {
    cc_node_data_t input = { .expr = cc_expr_log_ne };
    yylval.lexic_value = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    V_LOG_LEXER("OP_NE");
    return TK_OC_NE;
    }
<NORMAL>{OP_AND}                       {
    cc_node_data_t input = { .expr = cc_expr_log_and };
    yylval.lexic_value = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    V_LOG_LEXER("OP_AND");
    return TK_OC_AND;
    }
<NORMAL>{OP_OR}                        {
    cc_node_data_t input = { .expr = cc_expr_log_or };
    yylval.lexic_value = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    V_LOG_LEXER("OP_OR");
    return TK_OC_OR;
    }
<NORMAL>{OP_SL}                        {
    cc_node_data_t input = { .cmd = cc_cmd_shift_left };
    yylval.lexic_value = cc_create_lexic_value(input, cc_cmd, cc_match_line_number());
    V_LOG_LEXER("OP_SL");
    return TK_OC_SL;
    }
<NORMAL>{OP_SR}                        {
    cc_node_data_t input = { .cmd = cc_cmd_shift_right };
    yylval.lexic_value = cc_create_lexic_value(input, cc_cmd, cc_match_line_number());
    V_LOG_LEXER("OP_SR");
    return TK_OC_SR;
    }

    /* special characters */
<NORMAL>{SPC_CHAR}/{WHITE}?            {
    V_LOG_LEXER("SPECIAL");
    return (int)*yytext;
    }


    /* ---------- literals section ----------  */

    /* string literals */
<NORMAL>"\""                           { BEGIN(STRING); yymore(); V_LOG_LEXER("STRING STATE"); }
<STRING>("\\".|[^\"\n\\])*"\""         {
    /* TODO: add read string to global set */
    char* converted_string = cc_convert_escape_codes(yytext + 1, yyleng - 2);
    cc_node_data_t input = { .lit = { cc_type_string , { .string = converted_string } } };
    yylval.lexic_value = cc_create_lexic_value(input, cc_lit, cc_match_line_number());
    BEGIN(NORMAL);
    V_LOG_LEXER("QUOTED STRING");
    return TK_LIT_STRING;
    }
<STRING>{GRAPH}                        {
    yyless(1);
    BEGIN(NORMAL);
    V_LOG_LEXER("MALFORMED STRING");
    return TOKEN_ERRO;
    }

    /* character literals */
<NORMAL>"\'"                           { BEGIN(QUOTE); yymore(); V_LOG_LEXER("CHAR STATE"); }
<QUOTE>("\\".|[^\'\n\\])"\'"           {
    cc_node_data_t input;
    if (yyleng > 3) {
        char* escaped_char = cc_convert_escape_codes(yytext + 1, 2);
        input.lit.value.character = escaped_char[0];
        free(escaped_char);
    } else {
        input.lit.value.character = yytext[1];
    }
    input.lit.type = cc_type_char;
    yylval.lexic_value = cc_create_lexic_value(input, cc_lit, cc_match_line_number());
    BEGIN(NORMAL);
    V_LOG_LEXER("QUOTED CHARACTER");
    return TK_LIT_CHAR;
    }
<QUOTE>{GRAPH}                         {
    yyless(1);
    BEGIN(NORMAL);
    V_LOG_LEXER("MALFORMED QUOTE");
    return TOKEN_ERRO;
    }

    /* number literals */
<NORMAL>{NUMBER}/{ALNUM}*              {
    BEGIN(DECIMAL);
    V_LOG_LEXER("DECIMAL STATE");
    yycolumn--;
    yyless(0);
    }

    /* decimal state */
<DECIMAL>{

    /* float */
{NUMBER}+"."{NUMBER}+{SCI_NOT}?        {
    cc_node_data_t input = { .lit = { cc_type_float, { .floating = atof(yytext) } } };
    yylval.lexic_value = cc_create_lexic_value(input, cc_lit, cc_match_line_number());
    BEGIN(NORMAL);
    V_LOG_LEXER("FLOATING POINT");
    return TK_LIT_FLOAT;
    }

    /* malformed float */
{NUMBER}+"."{ALNUM}+                   {
    BEGIN(NORMAL);
    V_LOG_LEXER("MALFORMED FLOATING POINT");
    return TOKEN_ERRO;
    }

    /* integer */
{NUMBER}+                              {
    cc_node_data_t input = { .lit = { cc_type_int, { .integer = atoi(yytext) } } };
    yylval.lexic_value = cc_create_lexic_value(input, cc_lit, cc_match_line_number());
    BEGIN(NORMAL);
    V_LOG_LEXER("INTEGER");
    return TK_LIT_INT;
    }

    /* malformed decimal */
{ALNUM}+                               {
    BEGIN(NORMAL);
    V_LOG_LEXER("MALFORMED DECIMAL");
    return TOKEN_ERRO;
    }

}


    /* ---------- misc section ----------  */

    /* whitespace or newlines between tokens */
<NORMAL>{WHITE}+
    /* same thing as the first line, but we read the whole next line */
<NORMAL>\n.*                           {
    cc_update_line_buffer(yytext, yyleng);
    yycolumn = 1;
    yyless(1);
    }

    /* error catch-all */
<*>.                                   { V_LOG_LEXER("UNKNOWN"); return TOKEN_ERRO; }

%%
