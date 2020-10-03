/** string.h
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
 *
 */

#ifndef _STRING_H_
#define _STRING_H_

#include <string.h>
#include <stdlib.h>

#include "utils/debug.h"

char* cc_convert_escape_codes(const char* input, size_t limit);

#endif /* _STRING_H_ */
