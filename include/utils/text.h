/** @file utils/text.h
 *
 * @brief Text related utilities.
 *
 * @copyright (C) 2020 Henrique Silva
 *
 *
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 *
 * @section LICENSE
 *
 * This file is subject to the  terms and conditions defined in the file
 * 'LICENSE', which is part of this source code package.
 *
 * @section DESCRIPTION
 *
 * String conversion and other text  related procedures implemented in a
 * convenient way.
 */

#ifndef _UTILS_TEXT_H_
#define _UTILS_TEXT_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "utils/debug.h"
#include "utils/memory.h"

/* --------------------------------------------------------------------------- */
/* Function prototypes: */

/**
 * Copies  the input  string up  until limit  and converts  the explicit
 * escape codes into their respective escape code characters. The caller
 * must free the returned string.
 *
 * @param input the original string.
 * @param limit limit of the input character array.
 *
 * @return a duplicated converted version of the input string.
 */
char* cc_text_convert_escapes(
    char const* input,
    size_t      limit);

/**
 * Prints a string that underlines a given starting point and range.
 *
 * @param size desired final size of the string.
 * @param start the starting column.
 * @param end the ending column.
 */
void cc_text_underline(
    size_t   size,
    uint16_t start,
    uint16_t end);

#endif /* _UTILS_TEXT_H_ */
