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
    cc_map_t*   map   = cc_create_map(DEFAULT_MAP_SIZE, &cc_free_symbol_void);

    cc_push_stack(stack, (void*)map);

    return stack;
}

void cc_push_new_scope(void)
{
    cc_map_t* new_scope_map = cc_create_map(DEFAULT_MAP_SIZE, &cc_free_symbol_void);

    cc_push_stack(scope, (void*)new_scope_map);

    return;
}

void cc_pop_top_scope(void)
{
    cc_map_t* current_scope = cc_pop_stack(scope);

    cc_free_map(current_scope);

    return;
}

void cc_add_list_scope(cc_list_t* list)
{
    if (scope == NULL)
        scope = cc_init_global_scope();

    cc_map_t* top_scope = (cc_map_t*)cc_peek_stack(scope);

    while (list != NULL) {
        cc_symb_pair_t* aux = ((cc_symb_pair_t*)list->data);
        cc_insert_entry_map(top_scope, aux->name, (void*)aux->symbol);

        list = list->next;

        free(aux->name);
        free(aux);
    }

    return;
}

void cc_add_pair_scope(cc_symb_pair_t* pair)
{
    if (scope == NULL)
        scope = cc_init_global_scope();

    cc_map_t* top_scope = (cc_map_t*)cc_peek_stack(scope);

    cc_insert_entry_map(top_scope, pair->name, (void*)pair->symbol);

    free(pair->name);
    free(pair);

    return;
}

cc_query_answer_t cc_check_id_existence_scope(char const* name)
{
    cc_query_answer_t ret       = { cc_undeclared, NULL };
    cc_stack_t*       aux_stack = cc_create_stack(scope->size);
    bool              found     = false;
    bool              current   = true;

    while (!cc_is_empty_stack(scope) && found != true) {
        cc_map_t*  current_scope = cc_pop_stack(scope);
        cc_symb_t* symbol        = cc_get_entry_map(current_scope, name);

        if (symbol != NULL) {
            ret.where  = current == true ? cc_declared_current : cc_declared_previous;
            ret.symbol = symbol;

            found = true;
        }

        cc_push_stack(aux_stack, current_scope);
        current = false;
    }

    while (!cc_is_empty_stack(aux_stack))
        cc_push_stack(scope, cc_pop_stack(aux_stack));

    cc_free_stack(aux_stack);

    return ret;
}

void cc_check_name_usage_scope(
    char const*    name,
    cc_symb_kind_t kind)
{
    cc_query_answer_t answer = cc_check_id_existence_scope(name);

    if (answer.where == cc_undeclared) {
        // error!
    } else if (!cc_check_kind_symbol(answer.symbol, kind)) {
        // error!
    }
}
