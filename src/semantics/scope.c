/** @file scope.c
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

#include "semantics/scope.h"

/* --------------------------------------------------------------------------- */
/* Global declaration: */

cc_stack_t* scope = NULL;

/* --------------------------------------------------------------------------- */
/* Function definitions: */

cc_stack_t* cc_init_global_scope(void)
{
    cc_stack_t* stack = cc_create_stack(128);
    cc_map_t* map = cc_create_map(DEFAULT_MAP_SIZE);

    cc_push_stack(stack, (void*)map);

    return stack;
}

cc_stack_t* cc_add_list_scope(cc_stack_t* stack, cc_list_t* list)
{
    if (stack == NULL)
        stack = cc_init_global_scope();

    cc_map_t* top_scope = (cc_map_t*)cc_peek_stack(stack);
    cc_symb_pair_t* aux;

    while (list != NULL) {
        aux = ((cc_symb_pair_t*)list->data);
        cc_insert_entry_map(top_scope, aux->name, (void*)aux->symbol);

        list = list->next;
    }

    return stack;
}
