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

uint32_t cc_match_line(void)
{
    return (uint32_t)yylineno;
}

uint32_t cc_match_column(void)
{
    return (uint32_t)yylloc.first_column;
}

uint32_t cc_match_length(void)
{
    return (uint32_t)(yylloc.last_column - yylloc.first_column);
}

cc_location_t cc_match_location(void)
{
    return (cc_location_t) {cc_match_line(), cc_match_column(), cc_match_length()};
}

void cc_update_text_buffer(
    char* text,
    size_t match_length)
{
    if (yytextbuf == NULL)
        yytextbuf = cc_create_list(&free);

    cc_insert_list(yytextbuf, strndup(text, match_length));

    return;
}

void cc_print_location(
    cc_location_t  location,
    FILE* restrict stream)
{
    if (location.line > yytextbuf->size)
        return;

    char const* line = cc_access_list(yytextbuf, location.line);
    uint16_t size    = strlen(line);

    if (location.column > size)
        return;

    fprintf(stream, "%d:%d: appeared here:", location.line, location.column);

    fputs("\n    | ", stream);
    fputs(line, stream);
    fputs("\n    | ", stream);
    cc_text_underline(size + 1, location.column, location.column + location.length);
    fputs("\n", stdout);

    return;
}
