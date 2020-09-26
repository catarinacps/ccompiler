/** ast.h
 *
 * @file
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 * @author Bernardo Hummes <bhflores@inf.ufrgs.br>
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

#ifndef _AST_H_
#define _AST_H_

#include <stdbool.h>
#include <stdio.h>

typedef enum {
    cc_id,
    cc_lit,
    cc_expr,
    cc_comm
} cc_data_kind_t;

typedef union {
    char* text;
    double floating;
    int integer;
    char character;
    bool boolean;
} cc_literal_t;

typedef struct {
    cc_data_kind_t type;
    unsigned int line;
    bool is_const;
    bool is_static;
    cc_literal_t data;
} cc_lexic_value_t;

typedef struct cc_ast {
    cc_lexic_value_t content;
    size_t num_children;
    struct cc_ast* children;
} cc_ast_t;

#endif /* _AST_H_ */
