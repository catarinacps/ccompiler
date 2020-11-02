/** @file utils/text.c
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

#include "utils/text.h"

char* cc_text_convert_escapes(
    char const* input,
    size_t      limit)
{
    if (limit < 2) {
        D_PRINTF("tried to expand escape codes of string of size %lu\n", limit);
        return NULL;
    }

    char* new_string = (char*)cc_try_calloc(limit + 1, sizeof(char));

    /* ESC_SEQ [abfnrtv\\\"\'] */

    for (size_t i = 0, j = 0; i < limit; i++, j++) {
        if (input[i] == '\\') {
            switch (input[i + 1]) {
            case 'a':
                new_string[j] = '\a';
                break;
            case 'b':
                new_string[j] = '\b';
                break;
            case 'f':
                new_string[j] = '\f';
                break;
            case 'n':
                new_string[j] = '\n';
                break;
            case 'r':
                new_string[j] = '\r';
                break;
            case 't':
                new_string[j] = '\t';
                break;
            case 'v':
                new_string[j] = '\v';
                break;
            default:
                new_string[j] = input[i + 1];
            }

            i++;
        } else {
            new_string[j] = input[i];
        }
    }

    return new_string;
}

void cc_text_underline(
    size_t   size,
    uint16_t start,
    uint16_t end)
{
    char string[size];

    for (uint16_t i = 0; i < size; i++) {
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

    fputs(string, stdout);

    return;
}
