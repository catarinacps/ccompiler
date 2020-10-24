/** @file list.h
 * A simple linked list.
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
 * A simple  forward linked list  implementation. I'm well aware  of how
 * I've implemented  the same  thing over and  over again  throught this
 * source package.  This implementation shall  only be used  in semantic
 * operations, unless I change my mind later.
 */

#ifndef _LIST_H_
#define _LIST_H_

#include <stdint.h>

#include "utils/memory.h"

typedef struct cc_list_s {
    struct cc_list_s* next;
    void* data;
} cc_list_t;

/**
 * Inlined accessor  procedure. Takes an  index and tries to  return the
 * data associated to that index. No bounds checking is done here.
 *
 * @param list the list we wish to access.
 * @param index the index.
 *
 * @return the associated data.
 */
static inline void* cc_access_list(
    cc_list_t* list,
    uint32_t   index)
{
    for (uint32_t i = 0; i < index; i++)
        list = list->next;

    return list->data;
}

/**
 * Creates a new empty list in dynamic memory.
 *
 * @return the just created empty node.
 */
cc_list_t* cc_create_list();

/**
 * Frees a list.
 *
 * @param list the list you wish to free.
 */
void cc_free_list(cc_list_t* list);

/**
 * Inserts an item at the end of the list.
 *
 * @param list the list to add to.
 * @param item the item to add.
 *
 * @return the start of the list.
 */
cc_list_t* cc_insert_list(
    cc_list_t* list,
    void*      item);

/**
 * Append an item to the start of the list.
 *
 * @param list the list to add to.
 * @param item the item to add.
 *
 * @return the start of the list.
 */
cc_list_t* cc_append_list(
    cc_list_t* list,
    void*      item);

#endif /* _LIST_H_ */
