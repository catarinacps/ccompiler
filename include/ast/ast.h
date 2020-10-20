/** @file ast.h
 * An abstract syntax tree.
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
 * Implementation of an abstract syntax tree,  to be used in unison with
 * the bison implementation of a grammar.
 */

#ifndef _AST_H_
#define _AST_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "lexer/location.h"
#include "semantics/types.h"
#include "utils/debug.h"
#include "utils/memory.h"

/* --------------------------------------------------------------------------- */
/* Type definitions: */

typedef enum {
    cc_cmd_return,
    cc_cmd_continue,
    cc_cmd_break,
    cc_cmd_for,
    cc_cmd_while,
    cc_cmd_input,
    cc_cmd_output,
    cc_cmd_if,
    cc_cmd_shift_left,
    cc_cmd_shift_right,
    cc_cmd_atrib,
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
    cc_expr_log_gt,
    cc_expr_log_lt,
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

typedef enum {
    cc_id,
    cc_lit,
    cc_expr,
    cc_cmd,
    cc_func,
    cc_call
} cc_node_data_kind_t;

typedef union {
    char* id;
    cc_literal_t lit;
    cc_expression_t expr;
    cc_command_t cmd;
} cc_node_data_t;

typedef struct {
    cc_node_data_t data;
    cc_node_data_kind_t kind;
    cc_location_t location;
} cc_lexic_value_t;

typedef struct cc_ast_s {
    cc_lexic_value_t* content;
    uint8_t num_children;
    struct cc_ast_s** children;
    struct cc_ast_s* next;
} cc_ast_t;

/* pointer to global abstract syntax tree */
extern cc_ast_t* ast_g;
/* pointer to the alias of ast_g, arvore (again, terrible name) */
extern void*     arvore;

/* --------------------------------------------------------------------------- */
/* Function declarations: */

/**
 * Creates a new lexic value in dynamic memory.
 *
 * @param data the new lexic value data (a union, check above).
 * @param kind the type of node, an enum.
 * @param loc the location of match.
 *
 * @return the address of the created `cc_lexic_value_t`.
 *
 * @see the header "lexer/location.h".
 */
cc_lexic_value_t* cc_create_lexic_value(cc_node_data_t data, cc_node_data_kind_t kind, cc_location_t loc);

/**
 * Creates a  new AST  node in  dynamic memory.  The last  argument must
 * always be `NULL`, even when there are no children nodes.
 *
 * @param content a pointer to the lexic value you wish to assign to the node.
 * @param next a pointer to the next command, if there is any.
 * @param elipse a list of addresses to the children of this node, followed by a `NULL`.
 *
 * @return the address of the created `cc_ast_t`.
 */
cc_ast_t* cc_create_ast_node(cc_lexic_value_t* content, cc_ast_t* next, ...);

/**
 * Given two  nodes, set the  second node as  the next in  the (possible
 * multiple) first node(s).
 *
 * @param first a pointer to the first node. It can already have next nodes set.
 * @param second the future next node of the sequence.
 */
void cc_set_next_ast_node(cc_ast_t* first, cc_ast_t* second);

/**
 * Frees a lexic value type, given a pointer to it.
 *
 * @param value the pointer to the value.
 */
void cc_free_lexic_value(cc_lexic_value_t* value);

/**
 * Frees a single node of an AST, given a pointer to it.
 *
 * @param node the pointer to the node.
 */
void cc_free_ast_node(cc_ast_t* node);

/**
 * Frees an entire AST given its root pointer.
 *
 * @param ast the root of the AST.
 */
void cc_free_ast(cc_ast_t* ast);

/**
 * Inverts the signal of the given `cc_literal_t` if it's a numeric literal.
 *
 * @param num_literal the numeric literal to be inverted.
 *
 * @return an updated copy of the numeric literal.
 */
void cc_invert_number_literal(cc_literal_data_t* num_literal, cc_expression_t expr, cc_type_t type);

#endif /* _AST_H_ */
