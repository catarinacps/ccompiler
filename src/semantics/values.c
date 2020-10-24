/** @file values.c
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

#include "semantics/values.h"

cc_symb_t* cc_create_symbol(cc_location_t location, cc_symb_kind_t kind)
{
    cc_symb_t* new_symb = (cc_symb_t*)cc_try_malloc(sizeof(cc_symb_t));

    new_symb->location = location;
    new_symb->kind     = kind;
    new_symb->type     = cc_type_undef;

    return new_symb;
}

void cc_free_symbol(cc_symb_t* symbol)
{
    switch (symbol->kind) {
    case cc_symb_func:
        cc_free_list(symbol->optional_info.parameters);
        break;
    default:
        break;
    }

    free(symbol);

    return;
}

void cc_free_symbol_void(void* pointer)
{
    cc_free_symbol((cc_symb_t*)pointer);

    return;
}

cc_symb_pair_t* cc_create_symbol_pair(cc_lexic_value_t* lexic_value, cc_symb_kind_t kind)
{
    cc_symb_t*      new_symbol = cc_create_symbol(lexic_value->location, kind);
    cc_symb_pair_t* ret        = (cc_symb_pair_t*)cc_try_malloc(sizeof(cc_symb_pair_t));

    ret->symbol = new_symbol;
    ret->name   = strdup(lexic_value->data.id);

    if (kind != cc_symb_func) {
        cc_free_lexic_value(lexic_value);
    } else {
        ret->symbol->optional_info.temp_value = lexic_value;
    }

    return ret;
}

bool cc_init_type_symbol(cc_symb_t* symbol, cc_type_t type)
{
    if (symbol->type != cc_type_undef && symbol->type != type)
        return false;

    symbol->type = type;

    switch (type) {
    case cc_type_bool:
        symbol->size = 1;
        break;
    case cc_type_char:
        symbol->size = 1;
        break;
    case cc_type_float:
        symbol->size = 8;
        break;
    case cc_type_int:
        symbol->size = 4;
        break;
    case cc_type_string:
        symbol->size = 0;
        break;
    default:
        break;
    }

    return true;
}

cc_list_t* cc_init_type_list_symbols(cc_list_t* list, cc_type_t type)
{
    for (cc_list_t* i = list; i != NULL; i = i->next)
        if (cc_init_type_symbol(((cc_symb_pair_t*)i->data)->symbol, type) == false)
            return NULL;

    return list;
}

void cc_init_array_symbol(cc_symb_t* symbol, cc_lexic_value_t* lexic_value)
{
    if (symbol == NULL || symbol->kind != cc_symb_array)
        return;

    symbol->optional_info.quantity = lexic_value->data.lit.value.integer;

    cc_free_lexic_value(lexic_value);

    return;
}

void cc_init_func_symbol(cc_symb_t* symbol, cc_list_t* parameters)
{
    if (symbol == NULL || parameters == NULL || symbol->kind != cc_symb_func)
        return;

    symbol->optional_info.parameters = parameters;

    return;
}

void cc_init_string_symbol(cc_symb_t* symbol, uint32_t lenght)
{
    if (symbol == NULL || symbol->type != cc_type_string)
        return;

    /* the size of a string is sizeof(char) lenght, and sizeof(char) is 1 */
    symbol->size        = lenght;
    symbol->initialized = true;

    return;
}
