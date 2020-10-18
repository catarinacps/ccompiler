/** @file list.c
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

#include "semantics/list.h"
#include "utils/memory.h"

cc_list_t* cc_create_list()
{
    return (cc_list_t*)cc_try_calloc(1, sizeof(cc_list_t));
}

void cc_free_list(cc_list_t* list)
{
    if (list->next != NULL)
        cc_free_list(list->next);

    free(list);

    return;
}

cc_list_t* cc_insert_list(cc_list_t* list, void* item)
{
    cc_list_t* ret = list;

    while (list->next != NULL)
        list = list->next;

    if (list->data != NULL) {
        cc_list_t* new_node = cc_create_list();
        new_node->data = item;
        list->next = new_node;
    } else {
        list->data = item;
    }

    return ret;
}

cc_list_t* cc_append_list(cc_list_t* list, void* item)
{
    cc_list_t* new_node = cc_create_list();

    new_node->next = list;
    new_node->data = item;

    return new_node;
}
