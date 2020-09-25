/** debug.c
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

#include "utils/debug.h"
#include <stdlib.h>

void cc_die(const char* message, error_t code)
{
    perror(message);
    exit(code);
}
