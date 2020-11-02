/** @file tools.h
 * Lexer input info and screen output
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
 * Includes some utilities to printing things in the lexer.
 */

#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lexer/location.h"
#include "parser/parser.tab.h"
#include "utils/list.h"
#include "utils/memory.h"
#include "utils/text.h"

#ifndef VERBOSE
#define V_LOG_LEXER(STR)      ((void)0)
#define PRINT_NAME(TOKEN)     printf("%u " #TOKEN " [%s]\n", cc_match_line(), yytext)
#define PRINT_SPC_NAME(TOKEN) printf("%u TK_ESPECIAL [%c]\n", cc_match_line(), TOKEN)
#else
#define V_LOG_LEXER(STR)      printf("\n==> [%d]: " STR " {%s}\n", cc_match_line(), yytext)
#define PRINT_NAME(TOKEN)     ((void)0)
#define PRINT_SPC_NAME(TOKEN) ((void)0)
#endif

extern int yylineno;

extern cc_list_t* yytextbuf;

/**
 * Retrieves the line where the last token was recognized.
 *
 * @return the line number.
 */
uint32_t cc_match_line(void);

/**
 * Retrieves the column where the last token was recognized.
 *
 * @return the column number.
 */
uint32_t cc_match_column(void);

/**
 * Calculates the last match length.
 *
 * @return the last match length.
 */
uint32_t cc_match_length(void);

/**
 * Gets the location (line, column and length) of the last match.
 *
 * @return the `cc_location_t` of the match.
 *
 * @see the header "lexer/location.h".
 */
cc_location_t cc_match_location(void);

/**
 * Updates the global line buffer with the contents of `text` up until
 * `match_length`.
 *
 * @param text the input character array.
 * @param match_length the size of the input character array.
 */
void cc_update_text_buffer(
    char*  text,
    size_t match_length);

/**
 * Prints a given location of the text, if within the current boundaries
 * of the text.
 *
 * @param location the location of the point we wish to print.
 * @param stream were to print to.
 */
void cc_print_location(
    cc_location_t  location,
    FILE* restrict stream);

#endif /* _TOOLS_H_ */
