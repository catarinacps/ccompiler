/** base_types.h
 *
 * @copyright (C) 2020 Henrique Silva
 *
 *
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
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

#ifndef _BASE_TYPES_H_
#define _BASE_TYPES_H_

#include <stdbool.h>

/* --------------------------------------------------------------------------- */
/* Type definitions: */

typedef enum {
    cc_type_string,
    cc_type_float,
    cc_type_int,
    cc_type_char,
    cc_type_bool
} cc_type_t;

typedef enum {
    cc_cmd_return,
    cc_cmd_continue,
    cc_cmd_break,
    cc_cmd_for,
    cc_cmd_while,
    cc_cmd_input,
    cc_cmd_output,
    cc_cmd_if,
    /* cc_cmd_call, */
    cc_cmd_shift_left,
    cc_cmd_shift_right,
    /* cc_cmd_block, */
    cc_cmd_atrib,
    cc_cmd_decl,
    cc_cmd_init
} cc_command_t;

typedef enum {
    cc_expr_tern,
    cc_expr_bin_add,
    cc_expr_bin_sub,
    cc_expr_bin_mul,
    cc_expr_bin_div,
    cc_expr_bin_exp,
    cc_expr_bin_rem,
    cc_expr_bin_and,
    cc_expr_bin_or,
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
    cc_expr_un_index
} cc_expression_t;

typedef union {
    char* string;
    double floating;
    int integer;
    char character;
    bool boolean;
} cc_literal_data_t;

typedef struct {
    cc_type_t type;
    cc_literal_data_t value;
} cc_literal_t;

typedef struct {
    char* name;
    bool is_const;
    bool is_static;
    cc_type_t type;
} cc_identifier_t;

/**
 * Inverts the signal of the given `cc_literal_t` if it's a numeric literal.
 *
 * @param num_literal the numeric literal to be inverted.
 *
 * @return an updated copy of the numeric literal.
 */
void cc_invert_number_literal(cc_literal_data_t* num_literal, cc_expression_t expr, cc_type_t type);

#endif /* _BASE_TYPES_H_ */
