/** @file values.h
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
 * Definition of semantic values, i.e.  their meaning and content, to be
 * used in the hash map.
 */

#ifndef _VALUES_H_
#define _VALUES_H_

#include <stdbool.h>
#include <stdint.h>

#include "semantics/list.h"
#include "utils/memory.h"

typedef enum {
    cc_type_string,
    cc_type_float,
    cc_type_int,
    cc_type_char,
    cc_type_bool
} cc_symb_type_t;

typedef enum {
    cc_symb_var,
    cc_symb_func,
    cc_symb_array
} cc_symb_kind_t;

typedef union {
    uint16_t quantity;
    cc_list_t* parameters;
} cc_symb_opt;

typedef struct {
    uint32_t line;
    uint32_t column;
} cc_symb_loc_t;

typedef struct {
    cc_symb_loc_t location;
    cc_symb_kind_t kind;
    cc_symb_type_t type;
    uint8_t size;
    cc_symb_opt optional_info;
} cc_symb_t;

/**
 * Creates and initializes a new symbol in dynamic memory.
 *
 * @param location the location (line and column) of the symbol.
 * @param kind whether its a variable, an array or a function.
 * @param type the type of this symbol (int, char, bool, string, float).
 *
 * @return a new symbol allocated in the heap.
 */
cc_symb_t* cc_create_symbol(cc_symb_loc_t location, cc_symb_kind_t kind, cc_symb_type_t type);

/**
 * Initializes a symbol of an array, given an already existing symbol.
 *
 * @param symbol the symbol to add info to.
 * @param quantity how many elements are in the array.
 */
void cc_init_array_symbol(cc_symb_t* symbol, uint16_t quantity);

/**
 * Initializes a symbol of a function, given an already existing symbol.
 *
 * @param symbol the symbol to add info to.
 * @param names the names of the parameters, to be used as keys.
 */
void cc_init_func_symbol(cc_symb_t* symbol, cc_list_t* parameters);

/**
 * Initializes a symbol of a string variable, given an already existing symbol.
 *
 * @param symbol the symbol to be initialized.
 * @param lenght the lenght of the string.
 */
void cc_init_string_symbol(cc_symb_t* symbol, uint16_t lenght);

#endif /* _VALUES_H_ */
