/** parser.y - Syntax parser specification file
 *
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 * @author Bernardo Hummes <bhflores@inf.ufrgs.br>
 */

%code requires {
#include "ast/ast.h"
}

%code {
#include "parser/parser.h"
}

%union {
    cc_ast_t* node;
    cc_lexic_value_t* lexic_value;
}

/* all tokens, even the ones not utilized (as, in the first stage, we
 * did recognize them) */
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
%token <lexic_value> TK_LIT_INT
%token <lexic_value> TK_LIT_FLOAT
%token <lexic_value> TK_LIT_FALSE
%token <lexic_value> TK_LIT_TRUE
%token <lexic_value> TK_LIT_CHAR
%token <lexic_value> TK_LIT_STRING
%token <lexic_value> TK_IDENTIFICADOR
%token TOKEN_ERRO

%type <node> var_global
%type <node> function
%type <node> atrib
%type <node> var_local
%type <node> if
%type <node> for
%type <node> while
%type <node> io
%type <node> shift
%type <node> return
%type <node> call
%type <node> block
%type <node> op_tern
%type <node> op_log
%type <node> op_bws
%type <node> op_eq
%type <node> op_cmp
%type <node> op_add
%type <node> op_mul
%type <node> op_exp
%type <node> op_un

%type <lexic_value> integer float

/* the following options enable us more information when printing the
 * error */
%define parse.error verbose
%locations

%%

    /* ---------- GLOBAL SCOPE ---------- */

    /* the source code can be empty, and variables require ';' */
source: %empty
    | source var_global ';'
    | source function
    ;

var_global: type id_var_global_rep
    | TK_PR_STATIC type id_var_global_rep
    ;

    /* we can have multiple variables being initialized at once */
id_var_global_rep: id_var_global
    | id_var_global_rep ',' id_var_global
    ;

id_var_global: TK_IDENTIFICADOR '[' TK_LIT_INT ']'
    | TK_IDENTIFICADOR
    ;

function: header block
    ;

    /* definition parameters can be empty, as well as calling parameters */
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

    /* commands are chained through ';' */
command_rep: command_rep command ';'
    | command ';'
    ;

command: atrib
    | var_local
    | control_flow
    | io
    | shift
    | return
    | call
    | block
    ;

atrib: TK_IDENTIFICADOR '=' expr
    | TK_IDENTIFICADOR index '=' expr
    ;

var_local: type id_var_local_rep
    | TK_PR_STATIC type id_var_local_rep
    | TK_PR_CONST type id_var_local_rep
    | TK_PR_STATIC TK_PR_CONST type id_var_local_rep
    ;

    /* again, we can have multiple variables being declared at once */
id_var_local_rep: id_var_local
    | id_var_local_rep ',' id_var_local
    ;

    /* and they can be initialized (using "<=") */
id_var_local: TK_IDENTIFICADOR
    | TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR
    | TK_IDENTIFICADOR TK_OC_LE literal
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

while: TK_PR_WHILE '(' expr ')' TK_PR_DO block
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

param_rep: expr
    | param_rep ',' expr
    ;

    /* ---------- EXPRESSIONS ---------- */

    /* the expression rules are implemented following precedence orders */
expr: op_tern
    ;

op_tern: op_log
    | op_log '?' op_tern ':' op_tern
    ;

op_log: op_bws
    | op_bws tk_op_log op_log
    ;

op_bws: op_eq
    | op_eq tk_op_bws op_bws
    ;

op_eq: op_cmp
    | op_cmp tk_op_eq op_eq
    ;

op_cmp:  op_add
    | op_add tk_op_cmp op_cmp
    ;

op_add: op_mul
    | op_mul tk_op_add op_add
    ;

op_mul: op_exp
    | op_exp tk_op_mul op_mul
    ;

op_exp: op_un
    | op_un tk_op_exp op_exp
    ;

op_un: tk_op_un op_un
    | op_elem
    ;

op_elem: TK_IDENTIFICADOR
    | TK_IDENTIFICADOR index
    | TK_LIT_INT
    | TK_LIT_FLOAT
    | call
    | boolean
    | '(' expr ')'
    ;

    /* tokens of each expression rule */
tk_op_eq: TK_OC_EQ
    | TK_OC_NE
    ;

tk_op_log: TK_OC_AND
    | TK_OC_OR
    ;

tk_op_cmp: TK_OC_LE
    | TK_OC_GE
    ;

tk_op_add: '+'
    | '-'
    ;

tk_op_bws: '|'
    | '&'
    ;

tk_op_mul: '*'
    | '/'
    | '%'
    ;

tk_op_exp: '^'
    ;

tk_op_un: '*'
    | '&'
    | '#'
    | '+'
    | '-'
    | '!'
    | '?'
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
