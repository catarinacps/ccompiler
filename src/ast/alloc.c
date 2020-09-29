/** alloc.c
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

#include "ast/alloc.h"
#include "ast/ast.h"

cc_lexic_value_t* cc_create_lexic_value(
    cc_data_kind_t type,
    unsigned int line,
    bool is_const,
    bool is_static,
    cc_node_data_t data)
{
    cc_lexic_value_t* pointer = (cc_lexic_value_t*)cc_try_malloc(sizeof(cc_lexic_value_t));

    pointer->data = data;
    pointer->is_const = is_const;
    pointer->is_static = is_static;
    pointer->line = line;
    pointer->type = type;

    return pointer;
}
