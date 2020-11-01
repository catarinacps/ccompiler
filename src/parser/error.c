/** @file error.c
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

#include "parser/error.h"

void yyerror(char const* s, ...)
{
    va_list ap;
    va_start(ap, s);
    char* underline = cc_error_underline(yylloc.last_column + 2, yylloc.first_column, yylloc.last_column);

    if (yylloc.first_line)
        fprintf(stderr, "%d:%d: error: ", yylloc.first_line, yylloc.first_column);

    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n    | %s\n    | %s\n", (char*)yytextbuf->end->data, underline);

    free(underline);
    va_end(ap);

    return;
}

char* cc_error_underline(size_t size, unsigned int start, unsigned int end)
{
    char* string = (char*)cc_try_malloc((size + 1) * sizeof(char));

    for (unsigned int i = 0; i < size; i++) {
        if (i < start - 1) {
            string[i] = ' ';
        } else if (i == start - 1) {
            string[i] = '^';
        } else if (i < end) {
            string[i] = '~';
        } else {
            string[i] = ' ';
        }
    }

    string[size] = '\0';

    return string;
}
