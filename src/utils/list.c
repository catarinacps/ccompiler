/** @file utils/list.c
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

#include "utils/list.h"

cc_list_node_t* cc_create_list_node()
{
    return (cc_list_node_t*)cc_try_calloc(1, sizeof(cc_list_node_t));
}

cc_list_t* cc_create_list(void (*custom_free)(void*))
{
    cc_list_t* new_list   = (cc_list_t*)cc_try_calloc(1, sizeof(cc_list_t));
    new_list->custom_free = custom_free;

    return new_list;
}

void cc_free_list_nodes(
    cc_list_node_t* node,
    void          (*custom_free)(void*))
{
    if (node->next != NULL)
        cc_free_list_nodes(node->next, custom_free);

    (*custom_free)(node->data);
    free(node);

    return;
}

void cc_free_list(cc_list_t* list)
{
    if (list == NULL)
        return;

    cc_free_list_nodes(list->start, list->custom_free);

    free(list);

    return;
}

cc_list_t* cc_insert_list(
    cc_list_t* list,
    void*      item)
{
    cc_list_node_t* new_node = cc_create_list_node();
    new_node->data           = item;

    if (list->end != NULL) {
        list->end->next    = new_node;
        new_node->previous = list->end;
    } else {
        list->start = new_node;
    }

    list->end = new_node;
    list->size++;

    return list;
}

cc_list_t* cc_prepend_list(
    cc_list_t* list,
    void*      item)
{
    cc_list_node_t* new_node = cc_create_list_node();
    new_node->data           = item;

    if (list->start != NULL) {
        list->start->previous = new_node;
        new_node->next        = list->start;
    } else {
        list->end = new_node;
    }

    list->start = new_node;
    list->size++;

    return list;
}
