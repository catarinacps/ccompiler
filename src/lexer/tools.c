/** @file tools.c
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
 */

#include "lexer/tools.h"

uint32_t cc_match_line_number(void)
{
    return (uint32_t)yylineno;
}

uint32_t cc_match_column_number(void)
{
    return (uint32_t)yylloc.first_column;
}

cc_location_t cc_match_location(void)
{
    cc_location_t ret = {cc_match_line_number(), cc_match_column_number()};

    return ret;
}

void cc_update_line_buffer(char* text, size_t match_length)
{
    if (match_length + 1 > yylinebuf_len) {
        yylinebuf     = (char*)cc_try_realloc(yylinebuf, (match_length + 100) * sizeof(char));
        yylinebuf_len = match_length + 100;
    }
    strncpy(yylinebuf, text, yylinebuf_len - 1);
}
