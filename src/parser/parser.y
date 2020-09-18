%{
#include "parser/parser.h"
%}

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_DO
%token TK_PR_INPUT
%token TK_PR_OUTPUT
%token TK_PR_RETURN
%token TK_PR_CONST
%token TK_PR_STATIC
%token TK_PR_FOREACH
%token TK_PR_FOR
%token TK_PR_SWITCH
%token TK_PR_CASE
%token TK_PR_BREAK
%token TK_PR_CONTINUE
%token TK_PR_CLASS
%token TK_PR_PRIVATE
%token TK_PR_PUBLIC
%token TK_PR_PROTECTED
%token TK_PR_END
%token TK_PR_DEFAULT
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_OC_SL
%token TK_OC_SR
%token TK_OC_FORWARD_PIPE
%token TK_OC_BASH_PIPE
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_LIT_CHAR
%token TK_LIT_STRING
%token TK_IDENTIFICADOR
%token TOKEN_ERRO

%%

    /* ---------- GLOBAL SCOPE ---------- */

source: %empty
    | source global
    | source function
    ;

global: type id_global_rep ';'
    | TK_PR_STATIC type id_global_rep ';'
    ;

id_global_rep: id_global
    | id_global_rep ',' id_global
    ;

id_global: TK_IDENTIFICADOR '[' TK_LIT_INT ']'
    | TK_IDENTIFICADOR
    ;

function: header block
    ;

header: type TK_IDENTIFICADOR '(' def_params_rep ')'
    | TK_PR_STATIC type TK_IDENTIFICADOR '(' def_params_rep ')'
    | type TK_IDENTIFICADOR '(' ')'
    | TK_PR_STATIC type TK_IDENTIFICADOR '(' ')'
    ;

def_params_rep: def_params
    | def_params_rep ',' def_params
    ;

def_params: type TK_IDENTIFICADOR
    | TK_PR_CONST type TK_IDENTIFICADOR
    ;

block: '{' '}'
    | '{' command_rep '}'
    ;

    /* ---------- COMMANDS ---------- */

command_rep: command_rep command
    | command
    ;

command: atrib ';'
    | local ';'
    | control_flow ';'
    | io ';'
    | shift ';'
    | return ';'
    | block ';'
    | call ';'
    ;

atrib: TK_IDENTIFICADOR TK_OC_EQ expr
    | TK_IDENTIFICADOR index TK_OC_EQ expr
    ;

local: type id_local_rep
    | TK_PR_STATIC type id_local_rep
    | TK_PR_CONST type id_local_rep
    | TK_PR_STATIC TK_PR_CONST type id_local_rep
    ;

id_local_rep: id_local
    | id_local_rep ',' id_local
    ;

id_local: TK_IDENTIFICADOR
    | TK_IDENTIFICADOR TK_OC_EQ TK_IDENTIFICADOR
    | TK_IDENTIFICADOR TK_OC_EQ literal
    ;

control_flow: if
    | for
    | while
    ;

if: TK_PR_IF '(' expr ')' block
    | TK_PR_IF '(' expr ')' block TK_PR_ELSE block
    ;

for: TK_PR_FOR '(' atrib ':' expr ':' atrib ')' block
    ;

while: TK_PR_WHILE '(' expr ')' block
    ;

io: TK_PR_INPUT TK_IDENTIFICADOR
    | TK_PR_OUTPUT TK_IDENTIFICADOR
    | TK_PR_OUTPUT literal
    ;

shift: TK_IDENTIFICADOR op_shift integer
    | TK_IDENTIFICADOR index op_shift integer
    ;

return: TK_PR_RETURN expr
    | TK_PR_BREAK
    | TK_PR_CONTINUE
    ;

call: TK_IDENTIFICADOR '(' param_rep ')'
    | TK_IDENTIFICADOR '(' ')'
    ;

param_rep: param
    | param_rep ',' param
    ;

param: expr
    | literal
    | TK_IDENTIFICADOR
    ;

    /* ---------- EXPRESSIONS ---------- */

expr: 'a'
    ;

    /* ---------- LITERALS ----------  */

literal: decimal
    | boolean
    | TK_LIT_STRING
    | TK_LIT_CHAR
    ;

decimal: integer
    | float
    ;

integer: signal TK_LIT_INT
    | TK_LIT_INT
    ;

float: signal TK_LIT_FLOAT
    | TK_LIT_FLOAT
    ;

boolean: TK_LIT_TRUE
    | TK_LIT_FALSE
    ;

    /* ---------- MISC ----------  */

index: '[' expr ']'
    ;

signal: '+'
    | '-'
    ;

op_shift: TK_OC_SR
    | TK_OC_SL
    ;

type: TK_PR_INT
    | TK_PR_FLOAT
    | TK_PR_BOOL
    | TK_PR_CHAR
    | TK_PR_STRING
    ;

%%
