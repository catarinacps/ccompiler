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

cc_lexic_value_t* cc_alloc_lexic_literal(cc_literal_t value)
{
    cc_lexic_value_t* new_value;

    new_value = (cc_lexic_value_t*)malloc(sizeof(cc_lexic_value_t));

    if (new_value == NULL) {
        D_PRINTF("malloc just failed!\n");
        cc_die("out of memory", CC_OOMEM);
    }

    new_value->data = value;

    return new_value;
}
