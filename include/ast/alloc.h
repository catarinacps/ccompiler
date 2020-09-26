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

cc_lexic_value_t* cc_alloc_lexic_literal(cc_literal_t value);

#endif /* _ALLOC_H_ */
