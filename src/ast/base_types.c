/** @file base_types.c
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

#include "ast/base_types.h"

void cc_invert_number_literal(cc_literal_data_t* num_literal, cc_expression_t expr, cc_type_t type)
{
    /* do nothing if the given literal is of the incorrect type */
    if (expr == cc_expr_un_sign_neg) {
        if (type == cc_type_int)
            num_literal->integer = -num_literal->integer;
        else
            num_literal->floating = -num_literal->floating;
    }

    return;
}
