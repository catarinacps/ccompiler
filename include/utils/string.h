/** @file string.h
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
 *
 */

#ifndef _STRING_H_
#define _STRING_H_

#include <string.h>
#include <stdlib.h>

#include "utils/debug.h"
#include "utils/memory.h"

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
char* cc_convert_escape_codes(const char* input, size_t limit);

#endif /* _STRING_H_ */
