/** utils.h
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

#ifndef _PARSER_UTILS_H_
#define _PARSER_UTILS_H_

#include <stdio.h>

#include "lexer/scanner.h"
#include "lexer/utils.h"

/**
 * Prints to stderr a message with interesting information regarding the
 * current context.
 *
 * @param s the string you wish to print along with the current context.
 *
 * @return nothing
 */
void yyerror(char const* s);

#endif /* _PARSER_UTILS_H_ */
