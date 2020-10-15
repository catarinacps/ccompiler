/** @file aliases.h
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

#ifndef _ALIASES_H_
#define _ALIASES_H_

#include "ast/ast.h"
#include "ast/print.h"
#include "lexer/tools.h"

/**
 * An alias to the function `cc_print_ast`.
 *
 * @param raiz the void pointer to a `cc_ast_t` object.
 */
void exporta(void* raiz);

/**
 * An alias to the function `cc_free_ast`. Also cleans up flex's `yylinebuf`.
 *
 * @param raiz the void pointer to a `cc_ast_t` object.
 */
void libera(void* raiz);

#endif /* _ALIASES_H_ */
