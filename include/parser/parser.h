/** @file parser.h
 * Yacc parser header file
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
 * Cointains some basic declarations as of now. May change later.
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>

#include "lexer/scanner.h"
#include "semantics/scope.h"

/**
 * Prints to stderr a message with interesting information regarding the
 * current context.
 *
 * @param s the string you wish to print along with the current context.
 * @param elipse optional objects to format into the error string.
 */
void yyerror(
    char const*  s,
    /* format */ ...);

#endif /* _PARSER_H_ */
