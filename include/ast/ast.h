/** ast.h
 *
 * @file
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 * @author Bernardo Hummes <bhflores@inf.ufrgs.br>
 *
 * @section LICENSE
 *
 * This file is subject to the terms and conditions defined in the file
 * 'LICENSE', which is part of this source code package.
 *
 * @section DESCRIPTION
 *
 *
 */

#ifndef _AST_H_
#define _AST_H_

#include <stdbool.h>
#include <stdio.h>

typedef enum {
    cc_cmd_return,
    cc_cmd_continue,
    cc_cmd_break,
    cc_cmd_for,
    cc_cmd_while,
    cc_cmd_input,
    cc_cmd_output,
    cc_cmd_if,
    cc_cmd_call,
    cc_cmd_shift,
    cc_cmd_decl,
    cc_cmd_block,
    cc_cmd_atrib
} cc_command_t;

typedef enum {
    cc_expr_tern,
    cc_expr_bin_add,
    cc_expr_bin_sub,
    cc_expr_bin_mul,
    cc_expr_bin_div,
    cc_expr_bin_exp,
    cc_expr_bin_rem,
    cc_expr_bin_and_bws,
    cc_expr_bin_or_bws,
    cc_expr_log_and,
    cc_expr_log_or,
    cc_expr_log_ge,
    cc_expr_log_le,
    cc_expr_log_eq,
    cc_expr_log_ne,
    cc_expr_un_deref,
    cc_expr_un_addr,
    cc_expr_un_hash,
    cc_expr_un_sign_pos,
    cc_expr_un_sign_neg,
    cc_expr_un_negat,
    cc_expr_un_logic,
} cc_expression_t;

typedef union {
    char* string;
    double floating;
    int integer;
    char character;
    bool boolean;
} cc_literal_data_t;

typedef enum {
    cc_lit_string,
    cc_lit_float,
    cc_lit_int,
    cc_lit_char,
    cc_lit_bool
} cc_literal_kind_t;

typedef struct {
    cc_literal_kind_t type;
    cc_literal_data_t value;
} cc_literal_t;

typedef enum {
    cc_id,
    cc_lit,
    cc_expr,
    cc_comm
} cc_data_kind_t;

typedef union {
    char* id;
    cc_literal_t lit;
    cc_expression_t expr;
    cc_command_t comm;
} cc_node_data_t;

typedef struct {
    cc_data_kind_t type;
    unsigned int line;
    bool is_const;
    bool is_static;
    cc_node_data_t data;
} cc_lexic_value_t;

typedef struct cc_ast_s {
    cc_lexic_value_t content;
    size_t num_children;
    struct cc_ast_s* children;
} cc_ast_t;

#endif /* _AST_H_ */
