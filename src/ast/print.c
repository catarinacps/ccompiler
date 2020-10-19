/** @file print.c
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

#include "ast/print.h"

void cc_print_ast_children(cc_ast_t const* restrict node)
{
    for (unsigned int i = 0; i < node->num_children; i++)
        printf("%p, %p\n", (void*)node, (void*)node->children[i]);

    if (node->next != NULL)
        printf("%p, %p\n", (void*)node, (void*)node->next);

    return;
}

void cc_print_ast_node(cc_ast_t const* restrict node)
{
    printf("%p [label=\"", (void*)node);

    switch (node->content->kind) {
    case cc_call:
        printf("call %s", node->content->data.id);
        break;
    case cc_id:
    case cc_func:
        printf("%s", node->content->data.id);
        break;
    case cc_lit: {
        switch (node->content->data.lit.type) {
        case cc_type_string:
            printf("%s", node->content->data.lit.value.string);
            break;
        case cc_type_char:
            printf("%c", node->content->data.lit.value.character);
            break;
        case cc_type_int:
            printf("%d", node->content->data.lit.value.integer);
            break;
        case cc_type_float:
            printf("%.5f", node->content->data.lit.value.floating);
            break;
        case cc_type_bool:
            printf("%s", node->content->data.lit.value.boolean ? "true" : "false");
            break;
        case cc_type_undef:
            break;
        }
        break;
    }
    case cc_expr: {
        switch (node->content->data.expr) {
        case cc_expr_bin_add:
        case cc_expr_un_sign_pos:
            fputs("+", stdout);
            break;
        case cc_expr_bin_sub:
        case cc_expr_un_sign_neg:
            fputs("-", stdout);
            break;
        case cc_expr_bin_mul:
        case cc_expr_un_deref:
            fputs("*", stdout);
            break;
        case cc_expr_bin_div:
            fputs("/", stdout);
            break;
        case cc_expr_bin_exp:
            fputs("^", stdout);
            break;
        case cc_expr_bin_rem:
            fputs("%", stdout);
            break;
        case cc_expr_bin_or:
            fputs("|", stdout);
            break;
        case cc_expr_bin_and:
        case cc_expr_un_addr:
            fputs("&", stdout);
            break;
        case cc_expr_un_hash:
            fputs("#", stdout);
            break;
        case cc_expr_un_negat:
            fputs("!", stdout);
            break;
        case cc_expr_un_logic:
            fputs("?", stdout);
            break;
        case cc_expr_un_index:
            fputs("[]", stdout);
            break;
        case cc_expr_log_and:
            fputs("&&", stdout);
            break;
        case cc_expr_log_or:
            fputs("||", stdout);
            break;
        case cc_expr_log_ge:
            fputs(">=", stdout);
            break;
        case cc_expr_log_le:
            fputs("<=", stdout);
            break;
        case cc_expr_log_gt:
            fputs(">", stdout);
            break;
        case cc_expr_log_lt:
            fputs("<", stdout);
            break;
        case cc_expr_log_eq:
            fputs("==", stdout);
            break;
        case cc_expr_log_ne:
            fputs("!=", stdout);
            break;
        case cc_expr_tern:
            fputs("?:", stdout);
            break;
        }
        break;
    }
    case cc_cmd: {
        switch (node->content->data.cmd) {
        case cc_cmd_atrib:
            fputs("=", stdout);
            break;
        case cc_cmd_init:
            fputs("<=", stdout);
            break;
        case cc_cmd_shift_left:
            fputs("<<", stdout);
            break;
        case cc_cmd_shift_right:
            fputs(">>", stdout);
            break;
        case cc_cmd_for:
            fputs("for", stdout);
            break;
        case cc_cmd_while:
            fputs("while", stdout);
            break;
        case cc_cmd_if:
            fputs("if", stdout);
            break;
        case cc_cmd_break:
            fputs("break", stdout);
            break;
        case cc_cmd_continue:
            fputs("continue", stdout);
            break;
        case cc_cmd_return:
            fputs("return", stdout);
            break;
        case cc_cmd_input:
            fputs("input", stdout);
            break;
        case cc_cmd_output:
            fputs("output", stdout);
            break;
        }
    }
    }

    fputs("\"]\n", stdout);

    return;
}

void cc_print_ast(cc_ast_t const* restrict ast)
{
    if (ast == NULL)
        return;

    cc_print_ast_children(ast);

    for (unsigned int i = 0; i < ast->num_children; i++)
        cc_print_ast(ast->children[i]);

    if (ast->next != NULL)
        cc_print_ast(ast->next);

    cc_print_ast_node(ast);

    return;
}
