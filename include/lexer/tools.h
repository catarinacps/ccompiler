/** tools.h - Lexer input info and screen output
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

#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdio.h>
#include <string.h>

#include "utils/memory.h"

#ifndef VERBOSE
#define V_LOG_LEXER(STR) ((void)0)
#define PRINT_NAME(TOKEN) printf("%u " #TOKEN " [%s]\n", cc_match_line_number(), yytext)
#define PRINT_SPC_NAME(TOKEN) printf("%u TK_ESPECIAL [%c]\n", cc_match_line_number(), TOKEN)
#else
#define V_LOG_LEXER(STR) printf("\n==> [%d]: " STR " {%s}\n", cc_match_line_number(), yytext)
#define PRINT_NAME(TOKEN) ((void)0)
#define PRINT_SPC_NAME(TOKEN) ((void)0)
#endif

extern int yylineno;

extern char* yylinebuf;
extern size_t yylinebuf_len;

/**
 * Retrieves the line where the last token was recognized.
 *
 * @return the line number.
 */
unsigned int cc_match_line_number(void);

void cc_update_line_buffer(char* text, size_t match_lenght);

#endif /* _TOOLS_H_ */
