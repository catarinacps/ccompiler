/** @file scanner.h
 *
 * @brief Lexical analysis scanner header.
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
 * Includes the declaration of some functions that either the lexer
 * itself uses or other public functions to other modules.
 */

#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <stdio.h>
#include <string.h>

#include "ast/ast.h"
#include "lexer/tools.h"
#include "utils/debug.h"
#include "utils/text.h"

extern int yylex(void);
extern int yylex_destroy(void);

extern FILE* yyin;
extern char* yytext;
extern int   yycolumn;

#endif /* _SCANNER_H_ */
