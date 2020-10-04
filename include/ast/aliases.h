/** aliases.h
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

void exporta(void* raiz);

void libera(void* raiz);

#endif /* _ALIASES_H_ */
