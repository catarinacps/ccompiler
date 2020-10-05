/** memory.h - Memory related procedures
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
 * Wrappers over common dynamic memory management function.
 */

#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdio.h>
#include <stdlib.h>

#include "utils/debug.h"

/**
 * Tries to realloc the memory region, doing all required safety checks.
 *
 * @param pointer the existing memory block allocated with malloc, calloc or realloc.
 * @param new_size the desired new size.
 *
 * @return the pointer to the reallocated memory block.
 */
void* cc_try_realloc(void* pointer, size_t new_size);

/**
 * Tries to malloc the memory region, doing all required safety checks.
 *
 * @param desired_size the desired new size.
 *
 * @return the pointer to the memory block.
 */
void* cc_try_malloc(size_t desired_size);

/**
 * Tries to calloc a memory region, doing all required safety checks.
 *
 * @param quantity the number of blocks.
 * @param size the desired size of each block.
 *
 * @return the pointer to the memory block.
 */
void* cc_try_calloc(size_t quantity, size_t size);

#endif /* _MEMORY_H_ */
