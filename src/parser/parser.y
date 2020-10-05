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
    cc_expression_t expr; /* only here for explicit signals on numeric literals*/
}

/* all tokens, even the ones not utilized (as, in the first stage, we
 * did recognize them) */
%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token <lexic_value> TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token <lexic_value> TK_PR_WHILE
%token TK_PR_DO
%token <lexic_value> TK_PR_INPUT
%token <lexic_value> TK_PR_OUTPUT
%token <lexic_value> TK_PR_RETURN
%token TK_PR_CONST
%token TK_PR_STATIC
%token TK_PR_FOREACH
%token <lexic_value> TK_PR_FOR
%token TK_PR_SWITCH
%token TK_PR_CASE
%token <lexic_value> TK_PR_BREAK
%token <lexic_value> TK_PR_CONTINUE
%token TK_PR_CLASS
%token TK_PR_PRIVATE
%token TK_PR_PUBLIC
%token TK_PR_PROTECTED
%token TK_PR_END
%token TK_PR_DEFAULT
%token TK_OC_LE
%token <lexic_value> TK_OC_GE
%token <lexic_value> TK_OC_EQ
%token <lexic_value> TK_OC_NE
%token <lexic_value> TK_OC_AND
%token <lexic_value> TK_OC_OR
%token <lexic_value> TK_OC_SL
%token <lexic_value> TK_OC_SR
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

%type <node> source function
%type <lexic_value> header

%type <node> command command_rep
%type <node> atrib
%type <node> var_local id_var_local_rep id_var_local
%type <node> control_flow
%type <node> if
%type <node> for
%type <node> while
%type <node> io
%type <node> shift
%type <node> return
%type <node> call param_rep
%type <node> block

%type <node> expr
%type <node> op_tern op_log op_bws op_eq op_cmp
%type <node> op_add op_mul op_exp op_un op_elem
%type <node> index

%type <lexic_value> tk_op_eq tk_op_log tk_op_cmp tk_op_add
%type <lexic_value> tk_op_bws tk_op_mul tk_op_exp tk_op_un
%type <lexic_value> tk_cmd_atrib tk_cmd_init tk_cmd_shift

%type <lexic_value> literal decimal integer float boolean

%type <expr> signal

/* the following options enable us more information when printing the
 * error */
%define parse.error verbose
%locations

/* explicitly define the starting state as source */
%start source

%%

    /* ---------- GLOBAL SCOPE ---------- */

    /* the source code can be empty, and variables require ; */
source: %empty { $$ = NULL; }
    | source var_global ';'
    | source function {
    if ($1 != NULL) {
        $1->next = $2;
        $$ = $1;
    } else {
        $$ = $2;
    }
    ast_g = $$;
    arvore = (void*)$$;
    }
    ;

var_global: type id_var_global_rep
    | TK_PR_STATIC type id_var_global_rep
    ;

    /* we can have multiple variables being initialized at once */
id_var_global_rep: id_var_global
    | id_var_global_rep ',' id_var_global
    ;

id_var_global: TK_IDENTIFICADOR '[' TK_LIT_INT ']' { free($1->data.id); free($1); free($3); }
    | TK_IDENTIFICADOR { free($1->data.id); free($1); }
    ;

function: header block {
    $1->kind = cc_func;
    $$ = cc_create_ast_node($1, NULL, $2, NULL);
    }
    ;

    /* definition parameters can be empty, as well as calling parameters */
header: type TK_IDENTIFICADOR '(' def_params_rep ')' { $$ = $2; }
    | TK_PR_STATIC type TK_IDENTIFICADOR '(' def_params_rep ')' { $$ = $3; }
    | type TK_IDENTIFICADOR '(' ')' { $$ = $2; }
    | TK_PR_STATIC type TK_IDENTIFICADOR '(' ')' { $$ = $3; }
    ;

def_params_rep: def_params
    | def_params_rep ',' def_params
    ;

def_params: type TK_IDENTIFICADOR { free($2->data.id); free($2); }
    | TK_PR_CONST type TK_IDENTIFICADOR { free($3->data.id); free($3); }
    ;

block: '{' '}' { $$ = NULL; }
    | '{' command_rep '}' { $$ = $2; }
    ;

    /* ---------- COMMANDS ---------- */

    /* commands are chained through ; */
command_rep: command_rep command ';' {
    if ($1 == NULL) {
        $$ = $2;
    } else {
        if ($1->next == NULL) {
            $1->next = $2;
        } else {
            cc_ast_t *aux = $1->next, *cur = NULL;
            while (aux != NULL) {
                cur = aux;
                aux = aux->next;
            }
            cur->next = $2;
        }
        $$ = $1;
    }
    }
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

atrib: TK_IDENTIFICADOR tk_cmd_atrib expr {
    cc_ast_t* id_node = cc_create_ast_node($1, NULL, NULL);
    $$ = cc_create_ast_node($2, NULL, id_node, $3, NULL);
    }
    | TK_IDENTIFICADOR index tk_cmd_atrib expr {
    cc_node_data_t input = { .expr = cc_expr_un_index };
    cc_lexic_value_t* node_content = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    cc_ast_t* id_node = cc_create_ast_node($1, NULL, NULL);
    cc_ast_t* index_node = cc_create_ast_node(node_content, NULL, id_node, $2, NULL);

    $$ = cc_create_ast_node($3, NULL, index_node, $4, NULL);
    }
    ;

var_local: type id_var_local_rep { $$ = $2; }
    | TK_PR_STATIC type id_var_local_rep { $$ = $3; }
    | TK_PR_CONST type id_var_local_rep { $$ = $3; }
    | TK_PR_STATIC TK_PR_CONST type id_var_local_rep { $$ = $4; }
    ;

    /* again, we can have multiple variables being declared at once */
id_var_local_rep: id_var_local
    | id_var_local_rep ',' id_var_local {
    if ($1 == NULL) {
        $$ = $3;
    } else {
        $1->next = $3;
        $$ = $1;
    }
    }
    ;

    /* and they can be initialized (using <=) */
id_var_local: TK_IDENTIFICADOR { $$ = NULL; free($1->data.id); free($1); }
    | TK_IDENTIFICADOR tk_cmd_init TK_IDENTIFICADOR {
    cc_ast_t* id_node = cc_create_ast_node($1, NULL, NULL);
    cc_ast_t* init_val_node = cc_create_ast_node($3, NULL, NULL);
    $$ = cc_create_ast_node($2, NULL, id_node, init_val_node, NULL);
    }
    | TK_IDENTIFICADOR tk_cmd_init literal {
    cc_ast_t* id_node = cc_create_ast_node($1, NULL, NULL);
    cc_ast_t* init_val_node = cc_create_ast_node($3, NULL, NULL);
    $$ = cc_create_ast_node($2, NULL, id_node, init_val_node, NULL);
    }
    ;

control_flow: if
    | for
    | while
    ;

if: TK_PR_IF '(' expr ')' block { $$ = cc_create_ast_node($1, NULL, $3, $5, NULL); }
    | TK_PR_IF '(' expr ')' block TK_PR_ELSE block {
    $$ = cc_create_ast_node($1, NULL, $3, $5, $7, NULL);
    }
    ;

for: TK_PR_FOR '(' atrib ':' expr ':' atrib ')' block {
    $$ = cc_create_ast_node($1, NULL, $3, $5, $7, $9, NULL);
    }
    ;

while: TK_PR_WHILE '(' expr ')' TK_PR_DO block {
    $$ = cc_create_ast_node($1, NULL, $3, $6, NULL);
    }
    ;

io: TK_PR_INPUT TK_IDENTIFICADOR {
    cc_ast_t* id_node = cc_create_ast_node($2, NULL, NULL);
    $$ = cc_create_ast_node($1, NULL, id_node, NULL);
    }
    | TK_PR_OUTPUT TK_IDENTIFICADOR {
    cc_ast_t* id_node = cc_create_ast_node($2, NULL, NULL);
    $$ = cc_create_ast_node($1, NULL, id_node, NULL);
    }
    | TK_PR_OUTPUT literal {
    cc_ast_t* lit_node = cc_create_ast_node($2, NULL, NULL);
    $$ = cc_create_ast_node($1, NULL, lit_node, NULL);
    }
    ;

shift: TK_IDENTIFICADOR tk_cmd_shift integer {
    cc_ast_t* id_node = cc_create_ast_node($1, NULL, NULL);
    cc_ast_t* lit_node = cc_create_ast_node($3, NULL, NULL);
    $$ = cc_create_ast_node($2, NULL, id_node, lit_node, NULL);
    }
    | TK_IDENTIFICADOR index tk_cmd_shift integer {
    cc_node_data_t input = { .expr = cc_expr_un_index };
    cc_lexic_value_t* node_content = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    cc_ast_t* id_node = cc_create_ast_node($1, NULL, NULL);
    cc_ast_t* lit_node = cc_create_ast_node($4, NULL, NULL);
    cc_ast_t* index_node = cc_create_ast_node(node_content, NULL, id_node, $2, NULL);

    $$ = cc_create_ast_node($3, NULL, index_node, lit_node, NULL);
    }
    ;

return: TK_PR_RETURN expr { $$ = cc_create_ast_node($1, NULL, $2, NULL); }
    | TK_PR_BREAK { $$ = cc_create_ast_node($1, NULL, NULL); }
    | TK_PR_CONTINUE { $$ = cc_create_ast_node($1, NULL, NULL); }
    ;

call: TK_IDENTIFICADOR '(' param_rep ')' {
    $1->kind = cc_call;
    $$ = cc_create_ast_node($1, NULL, $3, NULL);
    }
    | TK_IDENTIFICADOR '(' ')' {
    $1->kind = cc_call;
    $$ = cc_create_ast_node($1, NULL, NULL);
    }
    ;

param_rep: expr
    | param_rep ',' expr { $1->next = $3; $$ = $1; }
    ;

    /* ---------- EXPRESSIONS ---------- */

    /* the expression rules are implemented following precedence orders */
expr: op_tern
    ;

op_tern: op_log
    | op_log '?' op_tern ':' op_tern {
    cc_node_data_t input = { .expr = cc_expr_tern };
    cc_lexic_value_t* node_content = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    $$ = cc_create_ast_node(node_content, NULL, $1, $3, $5, NULL);
    }
    ;

op_log: op_bws
    | op_bws tk_op_log op_log { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_bws: op_eq
    | op_eq tk_op_bws op_bws { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_eq: op_cmp
    | op_cmp tk_op_eq op_eq { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_cmp:  op_add
    | op_add tk_op_cmp op_cmp { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_add: op_mul
    | op_mul tk_op_add op_add { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_mul: op_exp
    | op_exp tk_op_mul op_mul { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_exp: op_un
    | op_un tk_op_exp op_exp { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_un: tk_op_un op_un { $$ = cc_create_ast_node($1, NULL, $2, NULL); }
    | op_elem
    ;

op_elem: TK_IDENTIFICADOR { $$ = cc_create_ast_node($1, NULL, NULL); }
    | TK_IDENTIFICADOR index {
    cc_node_data_t input = { .expr = cc_expr_un_index };
    cc_lexic_value_t* node_content = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    cc_ast_t* id_node = cc_create_ast_node($1, NULL, NULL);
    $$ = cc_create_ast_node(node_content, NULL, id_node, $2, NULL);
    }
    | TK_LIT_INT { $$ = cc_create_ast_node($1, NULL, NULL); }
    | TK_LIT_FLOAT { $$ = cc_create_ast_node($1, NULL, NULL); }
    | call
    | boolean { $$ = cc_create_ast_node($1, NULL, NULL); }
    | '(' expr ')' { $$ = $2; }
    ;

    /* tokens of each expression rule */
tk_op_eq: TK_OC_EQ
    | TK_OC_NE
    ;

tk_op_log: TK_OC_AND
    | TK_OC_OR
    ;

tk_op_cmp: TK_OC_LE {
    cc_node_data_t input = { .expr = cc_expr_log_le };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    | TK_OC_GE
    ;

tk_op_add: '+' {
    cc_node_data_t input = { .expr = cc_expr_bin_add };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    | '-' {
    cc_node_data_t input = { .expr = cc_expr_bin_sub };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    ;

tk_op_bws: '|' {
    cc_node_data_t input = { .expr = cc_expr_bin_or };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    | '&' {
    cc_node_data_t input = { .expr = cc_expr_bin_and };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    ;

tk_op_mul: '*' {
    cc_node_data_t input = { .expr = cc_expr_bin_mul };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    | '/' {
    cc_node_data_t input = { .expr = cc_expr_bin_div };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    | '%' {
    cc_node_data_t input = { .expr = cc_expr_bin_rem };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    ;

tk_op_exp: '^' {
    cc_node_data_t input = { .expr = cc_expr_bin_exp };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    ;

tk_op_un: '*' {
    cc_node_data_t input = { .expr = cc_expr_un_deref };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    | '&' {
    cc_node_data_t input = { .expr = cc_expr_un_addr };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    | '#' {
    cc_node_data_t input = { .expr = cc_expr_un_hash };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    | '+' {
    cc_node_data_t input = { .expr = cc_expr_un_sign_pos };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    | '-' {
    cc_node_data_t input = { .expr = cc_expr_un_sign_neg };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    | '!' {
    cc_node_data_t input = { .expr = cc_expr_un_negat };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
    | '?' {
    cc_node_data_t input = { .expr = cc_expr_un_logic };
    $$ = cc_create_lexic_value(input, cc_expr, cc_match_line_number());
    }
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

integer: signal TK_LIT_INT {
    cc_invert_number_literal(&($2->data.lit.value), $1, cc_type_int);
    $$ = $2;
    }
    | TK_LIT_INT
    ;

float: signal TK_LIT_FLOAT {
    cc_invert_number_literal(&($2->data.lit.value), $1, cc_type_float);
    $$ = $2;
    }
    | TK_LIT_FLOAT
    ;

boolean: TK_LIT_TRUE
    | TK_LIT_FALSE
    ;

    /* ---------- MISC ----------  */

index: '[' expr ']' { $$ = $2; }
    ;

signal: '+' { $$ = cc_expr_un_sign_pos; }
    | '-' { $$ = cc_expr_un_sign_neg; }
    ;

type: TK_PR_INT
    | TK_PR_FLOAT
    | TK_PR_BOOL
    | TK_PR_CHAR
    | TK_PR_STRING
    ;

tk_cmd_shift: TK_OC_SR
    | TK_OC_SL
    ;

tk_cmd_atrib: '=' {
    cc_node_data_t input = { .cmd = cc_cmd_atrib };
    $$ = cc_create_lexic_value(input, cc_cmd, cc_match_line_number());
    }
    ;

tk_cmd_init: TK_OC_LE {
    cc_node_data_t input = { .cmd = cc_cmd_init };
    $$ = cc_create_lexic_value(input, cc_cmd, cc_match_line_number());
    }
    ;

%%
