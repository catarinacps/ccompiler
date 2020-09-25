/** memory.c
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

#include "utils/memory.h"

void* cc_try_realloc(void* pointer, size_t new_size)
{
    void* new_pointer = NULL;

    new_pointer = realloc(pointer, new_size);

    if (new_pointer == NULL) {
        free(pointer);
        D_PRINTF("realloc just failed! required size was %u\n", new_size);

        cc_die("out of memory", CC_OOMEM);
    }

    return new_pointer;
}
