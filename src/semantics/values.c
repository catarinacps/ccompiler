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
#include "utils/memory.h"

cc_symb_t* cc_create_symbol(cc_symb_loc_t location, cc_symb_kind_t kind, cc_symb_type_t type)
{
    cc_symb_t* new_symb = (cc_symb_t*)cc_try_malloc(sizeof(cc_symb_t));

    new_symb->location = location;
    new_symb->kind = kind;
    new_symb->type = type;

    switch (type) {
    case cc_type_bool:
        new_symb->size = 1;
        break;
    case cc_type_char:
        new_symb->size = 1;
        break;
    case cc_type_float:
        new_symb->size = 8;
        break;
    case cc_type_int:
        new_symb->size = 4;
        break;
    case cc_type_string:
        new_symb->size = 0;
        break;
    }

    return new_symb;
}

void cc_init_array_symbol(cc_symb_t* symbol, uint16_t quantity)
{
    if (symbol == NULL)
        return;

    symbol->optional_info.quantity = quantity;

    return;
}

void cc_init_func_symbol(cc_symb_t* symbol, cc_list_t* parameters)
{
    if (symbol == NULL || parameters == NULL)
        return;

    symbol->optional_info.parameters = parameters;

    return;
}
