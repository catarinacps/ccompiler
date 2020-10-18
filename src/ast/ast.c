/** @file ast.c
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

#include "ast/ast.h"

/* declaration and definition of `ast_g` global */
cc_ast_t* ast_g = NULL;

cc_lexic_value_t* cc_create_lexic_value(cc_node_data_t data, cc_node_data_kind_t kind, uint32_t line)
{
    cc_lexic_value_t* pointer = (cc_lexic_value_t*)cc_try_malloc(sizeof(cc_lexic_value_t));

    pointer->data = data;
    pointer->line = line;
    pointer->kind = kind;

    return pointer;
}

cc_ast_t* cc_create_ast_node(cc_lexic_value_t* content, cc_ast_t* next, ...)
{
    va_list ap, aux;
    va_start(aux, next);
    va_copy(ap, aux);

    uint8_t param_count = 0;

    while (va_arg(aux, cc_ast_t*) != NULL)
        param_count++;

    va_end(aux); /* free the aux va_list */

    cc_ast_t* pointer = (cc_ast_t*)cc_try_malloc(sizeof(cc_ast_t));

    pointer->content = content;
    pointer->num_children = param_count;

    if (param_count > 0) {
        cc_ast_t** children = (cc_ast_t**)cc_try_malloc(param_count * sizeof(cc_ast_t*));

        for (uint8_t i = 0; i < param_count; i++)
            children[i] = va_arg(ap, cc_ast_t*);

        pointer->children = children;
    } else {
        pointer->children = NULL;
    }

    pointer->next = next;

    va_end(ap); /* free the main va_list */

    return pointer;
}

void cc_free_lexic_value(cc_lexic_value_t* value)
{
    if (value == NULL)
        return;

    switch (value->kind) {
    case cc_call:
    case cc_func:
    case cc_id:
        free(value->data.id);
        break;
    case cc_lit:
        if (value->data.lit.type == cc_type_string)
            free(value->data.lit.value.string);
        break;
    default:
        break;
    }

    free(value);

    return;
}

void cc_free_ast_node(cc_ast_t* node)
{
    if (node == NULL)
        return;

    cc_free_lexic_value(node->content);

    free(node->children);
    free(node);

    return;
}

void cc_free_ast(cc_ast_t* ast)
{
    if (ast == NULL)
        return;

    for (uint8_t i = 0; i < ast->num_children; i++)
        cc_free_ast(ast->children[i]);

    if (ast->next != NULL)
        cc_free_ast(ast->next);

    cc_free_ast_node(ast);

    return;
}

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
