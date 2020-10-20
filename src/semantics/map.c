/** @file map.c
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

#include "semantics/map.h"

/* --------------------------------------------------------------------------- */
/* Static declarations: */

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
static inline uint32_t cc_hash(char const* key);

/**
 * Creates a map entry in dynamic memory.
 *
 * @param key the key value.
 * @param value pointer to the contents of the key.
 *
 * @return a pointer to the node, allocated in dynamic memory.
 */
static inline cc_map_node_t* cc_create_entry_map(char const* key, void* value);

/**
 * Frees all entries in the collision list, considering `pointer` as the
 * head of the list.
 *
 * @param pointer a pointer to the node you wish to free both it and its collision list.
 */
static inline void cc_free_entry_list_map(cc_map_node_t* pointer);

/**
 * Frees a map entry.
 *
 * @param pointer a pointer to the node you wish to free.
 */
static inline void cc_free_entry_map(cc_map_node_t* pointer);

/**
 * Adds `new_item` to the collision list (or bucket) of `existing_item`.
 *
 * @param existing_item the first item added to some index, is the start of the list.
 * @param new_item the item to be added to the collision list of this index.
 */
static inline void cc_handle_collision_map(cc_map_node_t* existing_item, cc_map_node_t* new_item);

/* --------------------------------------------------------------------------- */
/* Function definitions: */

uint32_t cc_hash(char const* key)
{
    uint32_t hash = 3323198485ul;

    for (; *key; ++key) {
        hash ^= *key;
        hash *= 0x5bd1e995;
        hash ^= hash >> 15;
    }

    return hash;
}

cc_map_node_t* cc_create_entry_map(char const* key, void* value)
{
    cc_map_node_t* node = (cc_map_node_t*)cc_try_malloc(sizeof(cc_map_node_t));

    node->key   = strdup(key);
    node->value = value;
    node->next  = NULL;

    return node;
}

cc_map_t* cc_create_map(uint32_t size)
{
    cc_map_t* map = (cc_map_t*)cc_try_malloc(sizeof(cc_map_t));

    map->items = (cc_map_node_t**)cc_try_calloc(size, sizeof(cc_map_node_t*));
    map->size  = size;
    map->count = 0;

    return map;
}

void cc_free_entry_list_map(cc_map_node_t* pointer)
{
    if (pointer->next != NULL)
        cc_free_entry_map(pointer->next);

    cc_free_entry_map(pointer);

    return;
}

void cc_free_entry_map(cc_map_node_t* pointer)
{
    free(pointer->key);
    free(pointer);

    return;
}

void cc_free_map(cc_map_t* pointer)
{
    if (pointer == NULL)
        return;

    for (uint32_t i = 0; i < pointer->size; i++) {
        if (pointer->items[i] != NULL)
            cc_free_entry_list_map(pointer->items[i]);
    }

    free(pointer->items);
    free(pointer);

    return;
}

bool cc_insert_entry_map(cc_map_t* map, char const* key, void* value)
{
    if (map == NULL || key == NULL)
        return false;

    cc_map_node_t* new_item     = cc_create_entry_map(key, value);
    uint32_t       index        = cc_hash(key) % map->size;
    bool           success      = false;

    cc_map_node_t* current_item = map->items[index];

    if (current_item == NULL) {
        /* all is fine */
        map->items[index] = new_item;
        map->count++;

        success = true;
    } else if (map->count == map->size) {
        /* map is full! */
        D_PRINTF("failed insertion to hash map because all %lu items were filled\n", map->size);

        success = false;
    } else {
        /* collision! */
        cc_handle_collision_map(current_item, new_item);
        map->count++;

        success = true;
    }

    return success;
}

void* cc_get_entry_map(cc_map_t* map, char const* key)
{
    if (map == NULL || key == NULL)
        return NULL;

    cc_map_node_t* item = map->items[cc_hash(key) % map->size];

    while (item != NULL && strcmp(item->key, key) != 0)
        item = item->next;

    return item != NULL ? item->value : NULL;
}

void cc_handle_collision_map(cc_map_node_t* existing_item, cc_map_node_t* new_item)
{
    while (existing_item->next != NULL)
        existing_item = existing_item->next;

    existing_item->next = new_item;

    return;
}

void cc_delete_map_entry(cc_map_t* map, char const* key)
{
    if (map == NULL || key == NULL)
        return;

    uint32_t       index = cc_hash(key) % map->size;
    cc_map_node_t* item  = map->items[index];

    if (item == NULL)
        return;

    while (item->next != NULL && strcmp(item->next->key, key) != 0)
        item = item->next;

    if (item->next != NULL) {
        cc_free_entry_map(item->next);
        cc_map_node_t* new_next = item->next->next;

        item->next = new_next;
    } else if (strcmp(item->key, key) == 0) {
        cc_free_entry_map(item);

        map->items[index] = NULL;
    }

    map->count--;

    return;
}
