/** @file map.h
 * A char*-keyed hash map.
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
 * Contains the implementation of a hash table, all bateries included.
 */

#ifndef _MAP_H_
#define _MAP_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "utils/debug.h"
#include "utils/memory.h"

#define DEFAULT_MAP_SIZE ((uint32_t)521)

/* --------------------------------------------------------------------------- */
/* Type definitions: */

typedef struct cc_map_node_s {
    struct cc_map_node_s* next;
    void* value;
    char* key;
} cc_map_node_t;

typedef struct {
    uint32_t size; /** The size of this map. */
    uint32_t count; /** How many elements are occupied in this map. */
    cc_map_node_t** items; /** Pointer to the elements of the map. */
    void (*custom_free)(void*); /** Cleaning function to the elements of the map */
} cc_map_t;

/* --------------------------------------------------------------------------- */
/* Global function prototypes: */

/**
 * Creates the  map structure in dynamic  memory with the given  size in
 * the parameter `size`.
 *
 * @param size the size of the map.
 * @param custom_free the custom free function that will be used to free
 *                    the values when necessary.
 *
 * @return a pointer to the just created map.
 */
cc_map_t* cc_create_map(
    uint32_t size,
    void   (*custom_free)(void*));

/**
 * Frees a hash map.
 *
 * @param pointer a pointer to the map you wish to free.
 */
void cc_free_map(cc_map_t* pointer);

/**
 * Inserts an element to the given hash map.
 *
 * @param map the hash map we'll insert into.
 * @param key the key to use.
 * @param value the value that the given key should map to.
 *
 * @return a boolean indicating success.
 */
bool cc_insert_entry_map(
    cc_map_t*   map,
    char const* key,
    void*       value);

/**
 * Indexes the  map for  the given  key. If the  key doesn't  exist, the
 * return value will be `NULL`.
 *
 * @param map the hash map we'll index.
 * @param key the key we're looking for.
 *
 * @return the pointer to the value of the key or `NULL` on failure.
 */
void* cc_get_entry_map(
    cc_map_t*   map,
    char const* key);

/**
 * Deletes a map node from the given character key.
 *
 * @param map the map to delete from.
 * @param key the key we're looking to delete.
 */
void cc_delete_map_entry(
    cc_map_t*   map,
    char const* key);

#endif /* _MAP_H_ */
