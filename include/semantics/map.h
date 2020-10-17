/** @file map.h
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

typedef struct cc_map_node_s {
    struct cc_map_node_s* next;
    void* value;
    char* key;
} cc_map_node_t;

typedef struct {
    uint32_t size; /** The size of this map. */
    uint32_t count; /** How many elements are occupied in this map. */
    cc_map_node_t** items; /** Pointer to the elements of the map. */
} cc_map_t;

/**
 * Hashes   a  given   key  to   an  index.   Utilizes  the   MurmurHash
 * one-byte-at-a-time `uint32_t` implementation.
 *
 * @param key the key to hash.
 *
 * @return an unsigned integer index between [0, 4294967295).
 *
 * @see https://en.wikipedia.org/wiki/MurmurHash
 */
static uint32_t cc_hash(char const* key);

/**
 * Creates a map entry in dynamic memory.
 *
 * @param key the key value.
 * @param value pointer to the contents of the key.
 *
 * @return a pointer to the node, allocated in dynamic memory.
 */
static cc_map_node_t* cc_create_entry_map(char const* key, void* value);

/**
 * Creates the  map structure in dynamic  memory with the given  size in
 * the parameter `size`.
 *
 * @param size the size of the map.
 *
 * @return a pointer to the just created map.
 */
cc_map_t* cc_create_map(uint32_t size);

/**
 * Frees all entries in the collision list, considering `pointer` as the
 * head of the list.
 *
 * @param pointer a pointer to the node you wish to free both it and its collision list.
 */
static void cc_free_entry_list_map(cc_map_node_t* pointer);

/**
 * Frees a map entry.
 *
 * @param pointer a pointer to the node you wish to free.
 */
static void cc_free_entry_map(cc_map_node_t* pointer);

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
bool cc_insert_entry_map(cc_map_t* map, char const* key, void* value);

/**
 * Indexes the  map for  the given  key. If the  key doesn't  exist, the
 * return value will be `NULL`.
 *
 * @param map the hash map we'll index.
 * @param key the key we're looking for.
 *
 * @return the pointer to the value of the key or `NULL` on failure.
 */
void* cc_get_entry_map(cc_map_t* map, char const* key);

/**
 * Adds `new_item` to the collision list (or bucket) of `existing_item`.
 *
 * @param existing_item the first item added to some index, is the start of the list.
 * @param new_item the item to be added to the collision list of this index.
 */
static void cc_handle_collision_map(cc_map_node_t* existing_item, cc_map_node_t* new_item);

/**
 * Deletes a map node from the given character key.
 *
 * @param map the map to delete from.
 * @param key the key we're looking to delete.
 */
void cc_delete_map_entry(cc_map_t* map, char const* key);

#endif /* _MAP_H_ */
