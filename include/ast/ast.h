/** @file ast.h
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
#include <stdint.h>
#include <stdio.h>

#include "ast/base_types.h"
#include "utils/debug.h"
#include "utils/memory.h"

/* --------------------------------------------------------------------------- */
/* Type definitions: */

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
    uint32_t line;
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
extern void* arvore;

/* --------------------------------------------------------------------------- */
/* Function declarations: */

/**
 * Creates a new lexic value in dynamic memory.
 *
 * @param data the new lexic value data (a union, check above).
 * @param kind the type of node, an enum.
 * @param line the line of match.
 *
 * @return the address of the created `cc_lexic_value_t`.
 */
cc_lexic_value_t* cc_create_lexic_value(cc_node_data_t data, cc_node_data_kind_t kind, uint32_t line);

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
 */
void cc_free_lexic_value(cc_lexic_value_t* value);

/**
 */
void cc_free_ast_node(cc_ast_t* node);

/**
 */
void cc_free_ast(cc_ast_t* ast);

#endif /* _AST_H_ */
