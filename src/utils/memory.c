/** @file memory.c
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
        D_PRINTF("realloc just failed! error code %u\n", CC_ERR_OOMEM);
        D_PRINTF("required size was %lu\n", new_size);
        cc_die("out of memory", CC_ERR_OOMEM);
    }

    return new_pointer;
}

void* cc_try_malloc(size_t desired_size)
{
    void* new_pointer = malloc(desired_size);

    if (new_pointer == NULL) {
        D_PRINTF("malloc just failed! error code %u\n", CC_ERR_OOMEM);
        D_PRINTF("required size was %lu\n", desired_size);
        cc_die("out of memory", CC_ERR_OOMEM);
    }

    return new_pointer;
}

void* cc_try_calloc(size_t quantity, size_t size)
{
    void* new_pointer = calloc(quantity, size);

    if (new_pointer == NULL) {
        D_PRINTF("calloc just failed! error code %u\n", CC_ERR_OOMEM);
        D_PRINTF("required size was %lu blocks of size %lu\n", quantity, size);
        cc_die("out of memory", CC_ERR_OOMEM);
    }

    return new_pointer;
}
