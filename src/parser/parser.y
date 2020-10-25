/** @file parser.y
 * Syntax parser specification file.
 *
 * @copyright (C) 2020 Henrique Silva
 *
 *
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 */

%code requires {
#include "ast/ast.h"
#include "semantics/list.h"
#include "semantics/values.h"
}

%code {
#include "parser/parser.h"
}

%union {
    cc_ast_t* node;
    cc_lexic_value_t* lexic_value;
    cc_list_t* list;
    cc_symb_pair_t* pair;
    cc_type_t type;
    cc_expression_t expr; /* only here for explicit signals on numeric literals*/
}

/* all tokens, even the ones not utilized (as, in the first stage, we
 * did recognize them) */
%token <type> TK_PR_INT
%token <type> TK_PR_FLOAT
%token <type> TK_PR_BOOL
%token <type> TK_PR_CHAR
%token <type> TK_PR_STRING
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
%type <node> block func_block

%type <node> expr
%type <node> op_tern op_log op_bws op_eq op_cmp
%type <node> op_add op_mul op_exp op_un op_elem
%type <node> id_index id

%type <lexic_value> tk_op_eq tk_op_log tk_op_cmp tk_op_add
%type <lexic_value> tk_op_bws tk_op_mul tk_op_exp tk_op_un
%type <lexic_value> tk_cmd_atrib tk_cmd_init tk_cmd_shift

%type <node> literal decimal integer pos_int sign_int float pos_float sign_float boolean

%type <list> var_global id_var_global_rep
%type <pair> id_var_global

%type <list> header_params def_params_rep
%type <pair> def_params header_id

%type <type> type

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
source
    : %empty                { $$ = NULL; }
    | source var_global ';' { $$ = $1; cc_add_list_scope($2); }
    | source function       { $$ = cc_set_next_ast_node($1, $2); cc_update_global_ast($$); }
    ;

var_global
    : type id_var_global_rep              { $$ = cc_init_type_list_symbols($2, $1); }
    | TK_PR_STATIC type id_var_global_rep { $$ = cc_init_type_list_symbols($3, $2); }
    ;

    /* we can have multiple variables being initialized at once */
id_var_global_rep
    : id_var_global                       { $$ = cc_insert_list(cc_create_list(), (void*)$1); }
    | id_var_global_rep ',' id_var_global { $$ = cc_insert_list($1, (void*)$3); }
    ;

id_var_global
    : TK_IDENTIFICADOR '[' TK_LIT_INT ']' {
        $$ = cc_create_symbol_pair($1, cc_symb_array);
        cc_init_array_symbol($$->symbol, $3);
    }
    | TK_IDENTIFICADOR { $$ = cc_create_symbol_pair($1, cc_symb_var); }
    ;

function
    : header func_block {
        $1->kind = cc_func;
        $$ = cc_create_ast_node($1, NULL, $2, NULL);
    }
    ;

    /* definition parameters can be empty, as well as calling parameters */
header
    : header_id header_params {
        $$ = $1->symbol->optional_info.temp_value;
        cc_init_func_symbol($1->symbol, $2);
        cc_add_pair_scope($1);
        cc_push_new_scope();
        cc_add_list_scope($2);
    }
    ;

header_id
    : type TK_IDENTIFICADOR              { $$ = cc_create_symbol_pair($2, cc_symb_func); }
    | TK_PR_STATIC type TK_IDENTIFICADOR { $$ = cc_create_symbol_pair($3, cc_symb_func); }
    ;

header_params
    : '(' def_params_rep ')'             { $$ = $2; }
    | '(' ')'                            { $$ = NULL; }
    ;

def_params_rep
    : def_params                         { $$ = cc_insert_list(cc_create_list(), (void*)$1); }
    | def_params_rep ',' def_params      { $$ = cc_insert_list($1, (void*)$3); }
    ;

def_params
    : type TK_IDENTIFICADOR              { $$ = cc_create_symbol_pair($2, cc_symb_var); }
    | TK_PR_CONST type TK_IDENTIFICADOR  { $$ = cc_create_symbol_pair($3, cc_symb_var); }
    ;

func_block
    : '{' '}'                            { $$ = NULL; }
    | '{' command_rep close_scope        { $$ = $2; }
    ;

    /* ---------- COMMANDS ---------- */

    /* commands are chained through ; */
command_rep
    : command_rep command ';'            { $$ = cc_set_next_ast_node($1, $2); }
    | command ';'
    ;

command
    : atrib
    | var_local
    | control_flow
    | io
    | shift
    | return
    | call
    | block
    ;

block
    : '{' '}'                            { $$ = NULL; }
    | new_scope command_rep close_scope  { $$ = $2; }
    ;

new_scope
    : '{' { cc_push_new_scope(); }
    ;

close_scope
    : '}' { cc_pop_top_scope(); }
    ;

atrib
    : id tk_cmd_atrib expr       { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    | id_index tk_cmd_atrib expr { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

var_local
    : type id_var_local_rep                          { $$ = $2; }
    | TK_PR_STATIC type id_var_local_rep             { $$ = $3; }
    | TK_PR_CONST type id_var_local_rep              { $$ = $3; }
    | TK_PR_STATIC TK_PR_CONST type id_var_local_rep { $$ = $4; }
    ;

    /* again, we can have multiple variables being declared at once */
id_var_local_rep
    : id_var_local
    | id_var_local_rep ',' id_var_local { $$ = cc_set_next_ast_node($1, $3); }
    ;

    /* and they can be initialized (using <=) */
id_var_local
    : id                     { $$ = NULL; cc_free_ast_node($1); }
    | id tk_cmd_init id      { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    | id tk_cmd_init literal { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

control_flow
    : if
    | for
    | while
    ;

if
    : TK_PR_IF '(' expr ')' block { $$ = cc_create_ast_node($1, NULL, $3, $5, NULL); }
    | TK_PR_IF '(' expr ')' block TK_PR_ELSE block {
        $$ = cc_create_ast_node($1, NULL, $3, $5, $7, NULL);
    }
    ;

for
    : TK_PR_FOR '(' atrib ':' expr ':' atrib ')' block {
        $$ = cc_create_ast_node($1, NULL, $3, $5, $7, $9, NULL);
    }
    ;

while
    : TK_PR_WHILE '(' expr ')' TK_PR_DO block {
        $$ = cc_create_ast_node($1, NULL, $3, $6, NULL);
    }
    ;

io
    : TK_PR_INPUT id       { $$ = cc_create_ast_node($1, NULL, $2, NULL); }
    | TK_PR_OUTPUT id      { $$ = cc_create_ast_node($1, NULL, $2, NULL); }
    | TK_PR_OUTPUT literal { $$ = cc_create_ast_node($1, NULL, $2, NULL); }
    ;

shift
    : id tk_cmd_shift integer       { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    | id_index tk_cmd_shift integer { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

return
    : TK_PR_RETURN expr { $$ = cc_create_ast_node($1, NULL, $2, NULL); }
    | TK_PR_BREAK       { $$ = cc_create_ast_node($1, NULL, NULL); }
    | TK_PR_CONTINUE    { $$ = cc_create_ast_node($1, NULL, NULL); }
    ;

call
    : TK_IDENTIFICADOR '(' param_rep ')' {
        $1->kind = cc_call;
        $$ = cc_create_ast_node($1, NULL, $3, NULL);
    }
    | TK_IDENTIFICADOR '(' ')' {
        $1->kind = cc_call;
        $$ = cc_create_ast_node($1, NULL, NULL);
    }
    ;

param_rep
    : expr
    | param_rep ',' expr { $$ = cc_set_next_ast_node($1, $3); }
    ;

    /* ---------- EXPRESSIONS ---------- */

    /* the expression rules are implemented following precedence orders */
expr
    : op_tern
    ;

op_tern
    : op_log
    | op_log '?' op_tern ':' op_tern {
        cc_lexic_value_t* node_content = cc_create_lexic_value(
            (cc_node_data_t) { .expr = cc_expr_tern },
            cc_expr, cc_type_undef, cc_match_location());

        $$ = cc_create_ast_node(node_content, NULL, $1, $3, $5, NULL);
    }
    ;

op_log
    : op_bws
    | op_log tk_op_log op_bws { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_bws
    : op_eq
    | op_bws tk_op_bws op_eq  { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_eq
    : op_cmp
    | op_eq tk_op_eq op_cmp   { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_cmp
    :  op_add
    | op_cmp tk_op_cmp op_add { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_add
    : op_mul
    | op_add tk_op_add op_mul { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_mul
    : op_exp
    | op_mul tk_op_mul op_exp { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_exp
    : op_un
    | op_exp tk_op_exp op_un  { $$ = cc_create_ast_node($2, NULL, $1, $3, NULL); }
    ;

op_un
    : tk_op_un op_un          { $$ = cc_create_ast_node($1, NULL, $2, NULL); }
    | op_elem
    ;

op_elem
    : id           { $$ = $1; cc_check_name_usage_scope($1->content->data.id, cc_symb_var); }
    | id_index     {
        $$ = $1;
        cc_ast_t* id_node = cc_get_nth_child_node($1, 1);
        cc_check_name_usage_scope(id_node->content->data.id, cc_symb_array);
    }
    | pos_int
    | pos_float
    | call         { $$ = $1; cc_check_name_usage_scope($1->content->data.id, cc_symb_func); }
    | boolean
    | '(' expr ')' { $$ = $2; }
    ;

    /* tokens of each expression rule */
tk_op_eq
    : TK_OC_EQ
    | TK_OC_NE
    ;

tk_op_log
    : TK_OC_AND
    | TK_OC_OR
    ;

tk_op_cmp
    : TK_OC_LE {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_log_le },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    | TK_OC_GE
    | '>' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_log_gt },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    | '<' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_log_lt },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    ;

tk_op_add
    : '+' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_bin_add },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    | '-' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_bin_sub },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    ;

tk_op_bws
    : '|' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_bin_or },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    | '&' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_bin_and },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    ;

tk_op_mul
    : '*' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_bin_mul },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    | '/' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_bin_div },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    | '%' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_bin_rem },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    ;

tk_op_exp
    : '^' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_bin_exp },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    ;

tk_op_un
    : '*' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_un_deref },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    | '&' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_un_addr },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    | '#' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_un_hash },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    | '+' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_un_sign_pos },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    | '-' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_un_sign_neg },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    | '!' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_un_negat },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    | '?' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .expr = cc_expr_un_logic },
                                   cc_expr, cc_type_undef, cc_match_location());
    }
    ;

tk_cmd_atrib
    : '=' {
        $$ = cc_create_lexic_value((cc_node_data_t) { .cmd = cc_cmd_atrib },
                                   cc_cmd, cc_type_undef, cc_match_location());
    }
    ;

tk_cmd_init
    : TK_OC_LE {
        $$ = cc_create_lexic_value((cc_node_data_t) { .cmd = cc_cmd_init },
                                   cc_cmd, cc_type_undef, cc_match_location());
    }
    ;

    /* ---------- LITERALS ----------  */

literal
    : decimal
    | boolean
    | TK_LIT_STRING { $$ = cc_create_ast_node($1, NULL, NULL); }
    | TK_LIT_CHAR   { $$ = cc_create_ast_node($1, NULL, NULL); }
    ;

decimal
    : integer
    | float
    ;

integer
    : pos_int
    | sign_int
    ;

pos_int
    : TK_LIT_INT { $$ = cc_create_ast_node($1, NULL, NULL); }

sign_int
    : signal TK_LIT_INT {
        cc_invert_number_literal(&($2->data.lit), $1, cc_type_int);
        $$ = cc_create_ast_node($2, NULL, NULL);
    }

float
    : pos_float
    | sign_float
    ;

pos_float
    : TK_LIT_FLOAT { $$ = cc_create_ast_node($1, NULL, NULL); }

sign_float
    : signal TK_LIT_FLOAT {
        cc_invert_number_literal(&($2->data.lit), $1, cc_type_float);
        $$ = cc_create_ast_node($2, NULL, NULL);
    }

boolean
    : TK_LIT_TRUE  { $$ = cc_create_ast_node($1, NULL, NULL); }
    | TK_LIT_FALSE { $$ = cc_create_ast_node($1, NULL, NULL); }
    ;

    /* ---------- MISC ----------  */

id
    : TK_IDENTIFICADOR { $$ = cc_create_ast_node($1, NULL, NULL); }

id_index
    : id '[' expr ']' {
        cc_lexic_value_t* node_content = cc_create_lexic_value(
            (cc_node_data_t) { .expr = cc_expr_un_index },
            cc_expr, cc_type_undef, cc_match_location());

        $$ = cc_create_ast_node(node_content, NULL, $1, $3, NULL);
    }
    ;

signal
    : '+' { $$ = cc_expr_un_sign_pos; }
    | '-' { $$ = cc_expr_un_sign_neg; }
    ;

type
    : TK_PR_INT
    | TK_PR_FLOAT
    | TK_PR_BOOL
    | TK_PR_CHAR
    | TK_PR_STRING
    ;

tk_cmd_shift
    : TK_OC_SR
    | TK_OC_SL
    ;

%%
