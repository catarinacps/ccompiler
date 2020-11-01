/** @file utils/list.h
 *
 * @brief A simple linked list.
 *
 * @copyright (C) 2020 Henrique Silva
 *
 *
 * @author Henrique Silva <hcpsilva@inf.ufrgs.br>
 *
 * @section LICENSE
 *
 * This file is subject to the  terms and conditions defined in the file
 * 'LICENSE', which is part of this source code package.
 *
 * @section DESCRIPTION
 *
 * A simple  forward linked list  implementation. I'm well aware  of how
 * I've implemented  the same  thing over and  over again  throught this
 * source package.  This implementation shall  only be used  in semantic
 * operations, unless I change my mind later.
 */

#ifndef _UTILS_LIST_H_
#define _UTILS_LIST_H_

#include <stdint.h>

#include "utils/memory.h"

/* --------------------------------------------------------------------------- */
/* Type definitions: */

typedef struct cc_list_node_s {
    struct cc_list_node_s* next;
    struct cc_list_node_s* previous;
    void*                  data;
} cc_list_node_t;

typedef struct {
    cc_list_node_t* start;
    cc_list_node_t* end;
    uint32_t        size;
    void          (*custom_free)(void*);
} cc_list_t;

/* --------------------------------------------------------------------------- */
/* Global function prototypes: */

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
    cc_list_node_t* n = list->start;

    for (uint32_t i = 0; i != index; i++)
        n = n->next;

    return n->data;
}

/**
 * Creates a  list node in dynamic  memory. It is started  nulled out by
 * `calloc`.
 *
 * @return the created node.
 */
cc_list_node_t* cc_create_list_node();

/**
 * Creates a new empty list in dynamic memory.
 *
 * @param custom_free the custom free function that will be used to free
 *                    the values when necessary.
 *
 * @return the just created empty node.
 */
cc_list_t* cc_create_list(void (*custom_free)(void*));

/**
 * Frees all nodes following the received node, including itself.
 *
 * @param node the node to free.
 * @param custom_free the function to free the values when necessary.
 */
void cc_free_list_nodes(
    cc_list_node_t* node,
    void          (*custom_free)(void*));

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
cc_list_t* cc_prepend_list(
    cc_list_t* list,
    void*      item);

#endif /* _UTILS_LIST_H_ */
