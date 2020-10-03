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

#include <stdarg.h>
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
    unsigned int line;
} cc_lexic_value_t;

typedef struct cc_ast_s {
    cc_lexic_value_t* content;
    size_t num_children;
    struct cc_ast_s** children;
    struct cc_ast_s* next;
} cc_ast_t;

/* pointer to global abstract syntax tree */
extern cc_ast_t* ast_g;
/* and to its alias, arvore (again, terrible name) */
extern void* arvore;

/* --------------------------------------------------------------------------- */
/* Function declarations: */

/**
 */
void cc_export_ast(cc_ast_t* ast);

/**
 */
void cc_free_ast(cc_ast_t* ast);

/**
 * Creates a new lexic value in dynamic memory.
 *
 * @param data the new lexic value data (a union, check above).
 * @param kind the type of node, an enum.
 * @param line the line of match.
 *
 * @return the address of the created `cc_lexic_value_t`.
 */
cc_lexic_value_t* cc_create_lexic_value(cc_node_data_t data, cc_node_data_kind_t kind, unsigned int line);

/**
 * Creates a new AST node in dynamic memory. The last argument must
 * always be `NULL`, even when there are no children nodes.
 *
 * @param content a pointer to the lexic value you wish to assign to the node.
 * @param next a pointer to the next command, if there is any.
 * @param elipse a list of addresses to the children of this node, followed by a `NULL`.
 *
 * @return the address of the created `cc_ast_t`.
 */
cc_ast_t* cc_create_ast_node(cc_lexic_value_t* content, cc_ast_t* next, ...);

#endif /* _AST_H_ */
