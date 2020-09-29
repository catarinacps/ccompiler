/** alloc.h
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
 *
 */

#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdio.h>
#include <stdlib.h>

#include "ast/ast.h"
#include "utils/debug.h"
#include "utils/memory.h"

/**
 * Creates a new lexic value in dynamic memory.
 */
cc_lexic_value_t* cc_create_lexic_value(
    cc_data_kind_t type,
    unsigned int line,
    bool is_const,
    bool is_static,
    cc_node_data_t data);


#endif /* _ALLOC_H_ */
