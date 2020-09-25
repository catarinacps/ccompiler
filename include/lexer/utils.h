/** utils.h - Lexer input info and screen output
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
 * Includes some utilities to printing things in the lexer.
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>

#ifndef VERBOSE
#define V_LOG_LEXER(STR) ((void)0)
#define PRINT_NAME(TOKEN) printf("%u " #TOKEN " [%s]\n", get_line_number(), yytext)
#define PRINT_SPC_NAME(TOKEN) printf("%u TK_ESPECIAL [%c]\n", get_line_number(), TOKEN)
#else
#define V_LOG_LEXER(STR) printf("\n==> [%d]: " STR " {%s}\n", get_line_number(), yytext)
#define PRINT_NAME(TOKEN) ((void)0)
#define PRINT_SPC_NAME(TOKEN) ((void)0)
#endif

extern int yylineno;

/**
 * Retrieves the line where the last token was recognized.
 *
 * @return the line number.
 */
unsigned int get_line_number(void);

#endif /* _UTILS_H_ */
