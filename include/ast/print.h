/** @file print.h
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

#ifndef _PRINT_H_
#define _PRINT_H_

#include <stdio.h>

#include "ast/ast.h"

/**
 * Prints all children of a `cc_ast_t` node in CSV format. Every line
 * printed should be the node followed by a child after a ", ".
 *
 * @param node a pointer to a `cc_ast_t` node.
 */
void cc_print_ast_children(cc_ast_t const* restrict node);

/**
 * Prints the content of a `cc_ast_t` node, respecting its content.
 *
 * @param node a pointer to a `cc_ast_t` node.
 */
void cc_print_ast_node(cc_ast_t const* restrict node);

/**
 * Prints all content and children of the node, repeating the process for each child
 * node.
 *
 * @param ast a pointer to a `cc_ast_t` tree or subtree.
 */
void cc_print_ast(cc_ast_t const* restrict ast);

#endif /* _PRINT_H_ */
