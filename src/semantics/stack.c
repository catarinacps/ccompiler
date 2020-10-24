/** @file stack.c
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

#include "semantics/stack.h"

cc_stack_t* cc_create_stack(uint32_t capacity)
{
    cc_stack_t* stack = (cc_stack_t*)cc_try_malloc(sizeof(cc_stack_t));

    stack->size = capacity;
    stack->data = capacity > 0 ? (void**)cc_try_calloc(capacity, sizeof(void*)) : NULL;
    stack->top  = 0;

    return stack;
}

void cc_free_stack(cc_stack_t* pointer)
{
    if (pointer == NULL)
        return;

    if (pointer->data != NULL)
        free(pointer->data);
    free(pointer);

    return;
}

bool cc_is_full_stack(cc_stack_t* stack)
{
    if (stack == NULL)
        return false;

    return stack->top == stack->size;
}

bool cc_is_empty_stack(cc_stack_t* stack)
{
    if (stack == NULL)
        return false;

    return stack->top == 0;
}

bool cc_push_stack(
    cc_stack_t* stack,
    void*       item)
{
    if (stack == NULL || item == NULL)
        return false;

    if (cc_is_full_stack(stack)) {
        D_PRINTF("failed to push to stack, all %lu positions are full\n", stack->size);
        void** new_region = (void**)cc_try_calloc((stack->size + 1) * 2, sizeof(void*));

        if (stack->data != NULL) {
            memcpy(new_region, stack->data, stack->size);
            free(stack->data);
        }

        stack->data  = new_region;
        stack->size += stack->size + 1;
    }

    stack->data[stack->top] = item;

    stack->top++;

    return true;
}

void* cc_pop_stack(cc_stack_t* stack)
{
    if (stack == NULL)
        return NULL;

    if (cc_is_empty_stack(stack)) {
        D_PRINTF("failed to pop the stack of capacity %lu, it is empty\n", stack->size);
        return NULL;
    }

    return stack->data[--stack->top];
}

void* cc_peek_stack(cc_stack_t* stack)
{
    if (stack == NULL)
        return NULL;

    if (cc_is_empty_stack(stack)) {
        D_PRINTF("failed to pop the stack of capacity %lu, it is empty\n", stack->size);
        return NULL;
    }

    return stack->data[stack->top - 1];
}
