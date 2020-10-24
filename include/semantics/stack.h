/** @file stack.h
 * A generic stack implementation.
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
 * An array-implemented stack, with utility functions!
 */

#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "utils/debug.h"
#include "utils/memory.h"

/* --------------------------------------------------------------------------- */
/* Type definition: */

typedef struct {
    uint32_t size;
    uint32_t top;
    void** data;
} cc_stack_t;

/* --------------------------------------------------------------------------- */
/* Global function prototypes: */

/**
 * Creates a stack with given initial capacity.
 *
 * @param capacity the initial capacity.
 *
 * @return a pointer to the created stack, residing in the heap.
 */
cc_stack_t* cc_create_stack(uint32_t capacity);

/**
 * Frees the memory allocated for a given pointer to a stack.
 *
 * @param stack the stack to free.
 */
void cc_free_stack(cc_stack_t* pointer);

/**
 * Checks if the stack is full.
 *
 * @param stack the stack you wish to check.
 *
 * @return a boolean indicating whether it's full.
 */
bool cc_is_full_stack(cc_stack_t* stack);

/**
 * Checks if the stack is empty.
 *
 * @param stack the stack you wish to check.
 *
 * @return a boolean indicating whether it's empty.
 */
bool cc_is_empty_stack(cc_stack_t* stack);

/**
 * Pushes a given item to the top of the stack. Returns a boolean indicating success.
 *
 * @param stack the stack you wish to push to.
 * @param item the item you wish to push.
 *
 * @return a boolean indicating success.
 */
bool cc_push_stack(
    cc_stack_t* stack,
    void*       item);

/**
 * Pops the top of the stack. In case of failure, returns `NULL`.
 *
 * @param stack the stack we'll pop.
 *
 * @return the item that was in the top of the stack or `NULL`.
 */
void* cc_pop_stack(cc_stack_t* stack);

/**
 * Peeks at the first element of the stack. In case of failure, returns `NULL`.
 *
 * @param stack the stack to peek at.
 *
 * @return the item that is on the top or `NULL`.
 */
void* cc_peek_stack(cc_stack_t* stack);

#endif /* _STACK_H_ */
