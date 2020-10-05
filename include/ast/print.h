/** print.h
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
 */
void cc_print_ast_children(cc_ast_t const* restrict node);

/**
 */
void cc_print_ast_node(cc_ast_t const* restrict node);

/**
 */
void cc_print_ast(cc_ast_t const* restrict ast);

#endif /* _PRINT_H_ */
