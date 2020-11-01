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

/* --------------------------------------------------------------------------- */
/* Static declarations: */

cc_list_t* yytextbuf = NULL;

/* --------------------------------------------------------------------------- */
/* Function definitions: */

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
    return (cc_location_t) {cc_match_line_number(), cc_match_column_number()};
}

void cc_update_text_buffer(char* text, size_t match_length)
{
    if (yytextbuf == NULL)
        yytextbuf = cc_create_list(free);

    cc_insert_list(yytextbuf, strndup(text, match_length));

    return;
}
