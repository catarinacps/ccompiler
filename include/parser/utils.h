/** utils.h
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
 * Features functions that enhance the default bison error printing.
 */

#ifndef _PARSER_UTILS_H_
#define _PARSER_UTILS_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "lexer/scanner.h"
#include "lexer/utils.h"

/**
 * Prints to stderr a message with interesting information regarding the
 * current context.
 *
 * @param s the string you wish to print along with the current context.
 * @param elipse additional strings you may wish to print.
 *
 * @return nothing
 */
void yyerror(char const* s, ...);

/**
 * Allocates and returns a pointer to a string that underlines a given
 * starting point and range. You should free the pointer after using it.
 *
 * @param size desired final size of the string.
 * @param start the starting column.
 * @param end the ending column.
 *
 * @return a pointer to the generated string
 */
char* cc_parser_underline(size_t size, unsigned int start, unsigned int end);

#endif /* _PARSER_UTILS_H_ */
